EXECUTE BLOCK (
  Q_DATE_FROM   TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_FROM
 ,Q_DATE_TO     TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_TO
 ,Q_FIRM_IDS    TYPE OF COLUMN TABL$J_4.DOCSTR      = ?FIRM_IDS
 ,Q_PLACES_IDS  TYPE OF COLUMN TABL$J_4.DOCSTR      = ?PLACES_IDS
 ,Q_COUNTRY_IDS TYPE OF COLUMN TABL$J_4.DOCSTR      = ?COUNTRY_IDS
)RETURNS ( 
   DATE_FROM   TYPE OF COLUMN TABL$J_4.DATE_COMMIT
  ,DATE_TO     TYPE OF COLUMN TABL$J_4.DATE_COMMIT
  ,DATE_COMMIT TYPE OF COLUMN TABL$J_4.DATE_COMMIT
  ,FIRM_IDS    TYPE OF COLUMN TABL$J_4.DOCSTR
  ,PLACES_IDS  TYPE OF COLUMN TABL$J_4.DOCSTR
  ,COUNTRY_IDS TYPE OF COLUMN TABL$J_4.DOCSTR
  ,MBEG        TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO
  ,MDEB        TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO
  ,MKRD        TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO
  ,MKRD_       TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO
  ,MEND        TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO
  ,QBEG        TYPE OF COLUMN TABL$P_TMC_QUANT_MOVE.QUANT
  ,QDEB        TYPE OF COLUMN TABL$P_TMC_QUANT_MOVE.QUANT
  ,QKRD        TYPE OF COLUMN TABL$P_TMC_QUANT_MOVE.QUANT
  ,QKRD_       TYPE OF COLUMN TABL$P_TMC_QUANT_MOVE.QUANT
  ,QEND        TYPE OF COLUMN TABL$P_TMC_QUANT_MOVE.QUANT
)AS
  DECLARE VARIABLE P_MDEB TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO;
  DECLARE VARIABLE P_MKRD TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO;
  DECLARE VARIABLE P_QDEB TYPE OF COLUMN TABL$P_TMC_QUANT_MOVE.QUANT;
  DECLARE VARIABLE P_QKRD TYPE OF COLUMN TABL$P_TMC_QUANT_MOVE.QUANT;
BEGIN 
  DATE_FROM   = :Q_DATE_FROM;
  DATE_TO     = :Q_DATE_TO;
  FIRM_IDS    = :Q_FIRM_IDS;
  PLACES_IDS  = :Q_PLACES_IDS;
  COUNTRY_IDS = :Q_COUNTRY_IDS;
  SELECT COALESCE(SUM(P.QUANT),0), COALESCE(SUM(P.QUANT * TMC.MASSA_NETTO),0)
  FROM   TABL$P_TMC_QUANT_MOVE P, TABL$R_TMC TMC
  WHERE  (P.DATE_COMMIT < :DATE_FROM)
    AND  (:FIRM_IDS CONTAINING '~'||P.FIRM_ID||'~')
    AND  (:PLACES_IDS CONTAINING '~'||P.PLACE_ID||'~')
    AND  (P.FLAG_DEBET = 1)
    AND  (TMC.ID = P.TMC_ID)
    AND  (:COUNTRY_IDS  CONTAINING '~'||TMC.COUNTRY_ID||'~')
  INTO   :P_QDEB, :P_MDEB;
  SELECT COALESCE(SUM(P.QUANT),0), COALESCE(SUM(P.QUANT * TMC.MASSA_NETTO),0)
  FROM   TABL$P_TMC_QUANT_MOVE P, TABL$R_TMC TMC
  WHERE  (P.DATE_COMMIT < :DATE_FROM)
    AND  (:FIRM_IDS CONTAINING '~'||P.FIRM_ID||'~')
    AND  (:PLACES_IDS CONTAINING '~'||P.PLACE_ID||'~')
    AND  (P.FLAG_DEBET = 0)
    AND  (TMC.ID = P.TMC_ID)
    AND  (:COUNTRY_IDS  CONTAINING '~'||TMC.COUNTRY_ID||'~')
  INTO   :P_QKRD, :P_MKRD;

  MBEG = :P_MDEB - :P_MKRD;
  QBEG = :P_QDEB - :P_QKRD;
  DATE_COMMIT = :DATE_FROM;
  WHILE(:DATE_COMMIT < :DATE_TO)DO
    BEGIN
    SELECT COALESCE(SUM(P.QUANT),0), COALESCE(SUM(P.QUANT * TMC.MASSA_NETTO),0)
    FROM   TABL$P_TMC_QUANT_MOVE P, TABL$R_TMC TMC
    WHERE  (P.DATE_COMMIT BETWEEN :DATE_COMMIT AND DATEADD(1 DAY TO :DATE_COMMIT))
      AND  (:FIRM_IDS CONTAINING '~'||P.FIRM_ID||'~')
      AND  (:PLACES_IDS CONTAINING '~'||P.PLACE_ID||'~')
      AND  (P.FLAG_DEBET = 1)
      AND  (TMC.ID = P.TMC_ID)
      AND  (:COUNTRY_IDS  CONTAINING '~'||TMC.COUNTRY_ID||'~')
    INTO   :QDEB, :MDEB;
    SELECT COALESCE(SUM(P.QUANT),0), COALESCE(SUM(P.QUANT * TMC.MASSA_NETTO),0)
    FROM   TABL$P_TMC_QUANT_MOVE P, TABL$R_TMC TMC
    WHERE  (P.DATE_COMMIT BETWEEN :DATE_COMMIT AND DATEADD(1 DAY TO :DATE_COMMIT))
      AND  (:FIRM_IDS CONTAINING '~'||P.FIRM_ID||'~')
      AND  (:PLACES_IDS CONTAINING '~'||P.PLACE_ID||'~')
      AND  (P.FLAG_DEBET = 0)
      AND  (TMC.ID = P.TMC_ID)
      AND  (:COUNTRY_IDS CONTAINING '~'||TMC.COUNTRY_ID||'~')
    INTO   :QKRD, :MKRD;
    MKRD_ = 0 - :MKRD;
    QKRD_ = 0 - :QKRD;
    MEND  = MBEG + :MDEB - :MKRD;
    QEND  = QBEG + :QDEB - :QKRD;
    SUSPEND;
    MBEG = :MEND;
    QBEG = :QEND;
    DATE_COMMIT = DATEADD(1 DAY TO :DATE_COMMIT);
    END
END
