EXECUTE BLOCK (
  Q_DATE_FROM TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_FROM
 ,Q_DATE_TO   TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_TO
 ,Q_FIRM_IDS  TYPE OF COLUMN TABL$J_4.DOCSTR      = ?FIRM_IDS
)RETURNS ( 
  DATE_FROM           TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,DATE_TO             TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,P_DATE              TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,FIRM_IDS            TYPE OF COLUMN TABL$J_4.DOCSTR
 ,FIRM_NAMES          TYPE OF COLUMN TABL$J_4.DOCSTR
 ,BUHG_ACCS_ID        TYPE OF COLUMN TABL$R_BUHG_ACCS.ID
 ,BUHG_ACCS_PARENT_ID TYPE OF COLUMN TABL$R_BUHG_ACCS.PARENT_ID
 ,BUHG_ACCS_NAME      TYPE OF COLUMN TABL$R_BUHG_ACCS.NAME
 ,BUHG_ACCS_NAMEPATH  TYPE OF COLUMN TABL$J_4.DOCSTR
 ,BUHG_ACCS_IDS       TYPE OF COLUMN TABL$J_4.DOCSTR
 ,BUHG_ACCS_SALDO     TYPE OF COLUMN TABL$J_4.DOCSUM
 ,BUHG_ACCS_SALDODIFF TYPE OF COLUMN TABL$J_4.DOCSUM
 ,SALDOBEGIN          TYPE OF COLUMN TABL$J_4.DOCSUM
 ,DEBET               TYPE OF COLUMN TABL$J_4.DOCSUM
 ,KREDIT              TYPE OF COLUMN TABL$J_4.DOCSUM
 ,DAY_CNT             TYPE OF COLUMN TABL$J_4.ID
)AS
  DECLARE VARIABLE P_ACC_IDS TYPE OF COLUMN TABL$P_CND.ACC_IDS_DEB;
  DECLARE VARIABLE P_DEBET   TYPE OF COLUMN TABL$J_4.DOCSUM;
  DECLARE VARIABLE P_KREDIT  TYPE OF COLUMN TABL$J_4.DOCSUM;
BEGIN
  DATE_FROM = :Q_DATE_FROM;
  DATE_TO   = :Q_DATE_TO;
  FIRM_IDS  = :Q_FIRM_IDS;
  SELECT FIRST 1 LIST(F.NAME,'; ') FROM TABL$R_FIRMS F WHERE(:FIRM_IDS CONTAINING '~'||F.ID||'~') INTO :FIRM_NAMES;
  P_ACC_IDS = '';
  SELECT '~'||LIST(DISTINCT TMP.ACC_ID,'~')||'~'
  FROM   (SELECT DISTINCT CD.ACC_ID_DEB  AS ACC_ID FROM TABL$P_CND CD
          UNION ALL
          SELECT DISTINCT CD.ACC_ID_KRED AS ACC_ID FROM TABL$P_CND CD
          )TMP
  INTO    :P_ACC_IDS;
  DAY_CNT = DATEDIFF(DAY FROM :DATE_FROM TO :DATE_TO);
  FOR
    SELECT TMP.ID, TMP.PARENT_ID, TMP.NAME, TMP.NAMEPATH
    FROM   (WITH RECURSIVE BA AS(
              SELECT B1.ID, B1.PARENT_ID, B1.NAME, CAST('' AS VARCHAR(1)) AS NAMEPATH
              FROM   TABL$R_BUHG_ACCS B1
              WHERE  (B1.PARENT_ID = -1000000)
              UNION ALL
              SELECT B2.ID, B2.PARENT_ID, B2.NAME, CAST('  '||B3.NAMEPATH AS VARCHAR(255)) AS NAMEPATH
              FROM   TABL$R_BUHG_ACCS B2, BA B3
              WHERE  (B2.PARENT_ID = B3.ID)
            )SELECT B.ID, B.PARENT_ID, B.NAME, B.NAMEPATH FROM BA B
            )TMP
--    WHERE  (:P_ACC_IDS CONTAINING '~'||TMP.ID||'~')
    INTO   :BUHG_ACCS_ID, :BUHG_ACCS_PARENT_ID, :BUHG_ACCS_NAME, :BUHG_ACCS_NAMEPATH
  DO 
    BEGIN
    BUHG_ACCS_SALDO    = 0;
    BUHG_ACCS_NAMEPATH = :BUHG_ACCS_NAMEPATH||:BUHG_ACCS_NAME;
    DEBET  = 0; KREDIT = 0;
    SALDOBEGIN    = 0;
    WITH RECURSIVE BA AS(
      SELECT B1.ID, B1.PARENT_ID
      FROM   TABL$R_BUHG_ACCS B1
      WHERE  (B1.ID = :BUHG_ACCS_ID)
      UNION ALL
      SELECT B2.ID, B2.PARENT_ID
      FROM   TABL$R_BUHG_ACCS B2, BA B3
      WHERE  (B2.PARENT_ID = B3.ID)
    )
    SELECT COALESCE('~'||LIST(B.ID,'~')||'~', '')
    FROM   BA B
    WHERE  EXISTS(
             SELECT FIRST 1 C.ID
             FROM   TABL$P_CND C
             WHERE  ( (C.ACC_ID_DEB=B.ID) OR (C.ACC_ID_KRED=B.ID) )
               AND  (:FIRM_IDS CONTAINING '~'||C.FIRM_ID||'~')
           )
    INTO :BUHG_ACCS_IDS;
    IF( (:BUHG_ACCS_IDS <> '') --AND (:BUHG_ACCS_ID <> 0) 
    )THEN
      BEGIN
      SELECT COALESCE(SUM(C1.CND_VALUE),0)
      FROM   TABL$P_CND C1
      WHERE  (C1.DATE_COMMIT < :DATE_FROM)
        AND  (C1.ACC_IDS_DEB CONTAINING '~'||:BUHG_ACCS_ID||'~')
        AND  (:FIRM_IDS      CONTAINING '~'||C1.FIRM_ID||'~')
      INTO   :P_DEBET;
      SELECT COALESCE(SUM(C2.CND_VALUE),0)
      FROM   TABL$P_CND C2
      WHERE  (C2.DATE_COMMIT < :DATE_FROM)
        AND  (C2.ACC_IDS_KRED CONTAINING '~'||:BUHG_ACCS_ID||'~')
        AND  (:FIRM_IDS      CONTAINING '~'||C2.FIRM_ID||'~')
      INTO   :P_KREDIT;
      SALDOBEGIN = :P_DEBET - :P_KREDIT;
      IF(:SALDOBEGIN >= 0)THEN
        BEGIN
        DEBET = :SALDOBEGIN;
        END 
       ELSE
        BEGIN
        KREDIT = ABS(:SALDOBEGIN);
        END

      P_DATE = :DATE_FROM;
      WHILE(:P_DATE < :DATE_TO)DO
        BEGIN
        P_DEBET  = 0; P_KREDIT = 0;
        SELECT COALESCE(SUM(C1.CND_VALUE),0)
        FROM   TABL$P_CND C1
        WHERE  (C1.DATE_COMMIT BETWEEN :P_DATE AND DATEADD(1 DAY TO :P_DATE))
          AND  (C1.ACC_IDS_DEB CONTAINING '~'||:BUHG_ACCS_ID||'~')
          AND  (:FIRM_IDS      CONTAINING '~'||C1.FIRM_ID||'~')
        INTO   :P_DEBET;
        SELECT COALESCE(SUM(C2.CND_VALUE),0)
        FROM   TABL$P_CND C2
        WHERE  (C2.DATE_COMMIT BETWEEN :P_DATE AND DATEADD(1 DAY TO :P_DATE))
          AND  (C2.ACC_IDS_KRED CONTAINING '~'||:BUHG_ACCS_ID||'~')
          AND  (:FIRM_IDS       CONTAINING '~'||C2.FIRM_ID||'~')
        INTO   :P_KREDIT;
        SALDOBEGIN = :SALDOBEGIN + :P_DEBET - :P_KREDIT;
        IF(:SALDOBEGIN >= 0)THEN
          BEGIN
          DEBET  = :DEBET  + ABS(:SALDOBEGIN);
          END 
         ELSE
          BEGIN
          KREDIT = :KREDIT + ABS(:SALDOBEGIN);
          END
--        suspend;  
        P_DATE = DATEADD(1 DAY TO :P_DATE);
        END
      END
    DEBET  = :DEBET / :DAY_CNT;
    KREDIT = :KREDIT / :DAY_CNT;
    IF((:DEBET <> 0) OR (:KREDIT <> 0))THEN SUSPEND;
    END
END
