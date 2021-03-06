EXECUTE BLOCK(
  Q_J_ID    TYPE OF COLUMN TABL$J_4.ID     = ?J_ID
 ,Q_DOCSUM  TYPE OF COLUMN TABL$J_4.DOCSUM = ?DOCSUM
)AS
  DECLARE VARIABLE P_J_ID     TYPE OF COLUMN TABL$J_4.ID;
  DECLARE VARIABLE P_FIRM_ID  TYPE OF COLUMN TABL$J_4.FIRM_ID;
  DECLARE VARIABLE P_CS_ID    TYPE OF COLUMN TABL$J_1000014.CS_ID;
  DECLARE VARIABLE P_DOCNAME  TYPE OF COLUMN TABL$J_4.NAME;
BEGIN
  P_DOCNAME = '������ �� ����� ��� �� ������� ������';

  SELECT FIRST 1 J.FIRM_ID, JZ.CS_ID
  FROM   TABL$J_4 J, TABL$J_1000141 JZ
  WHERE  (J.ID = :Q_J_ID)
    AND  (JZ.J_ID = J.ID)
  INTO   :P_FIRM_ID, :P_CS_ID;

  SELECT FIRST 1 P.J_ID FROM PROC$J_INS_1000020(:P_FIRM_ID, :P_DOCNAME, :Q_J_ID) P INTO :P_J_ID;

  UPDATE TABL$J_4 J SET
     J.DOCSUMVAL  = :Q_DOCSUM
  WHERE (J.ID = :P_J_ID);

  UPDATE TABL$J_1000016 JC SET
     JC.ACC_ID      = 361
    ,JC.SUBKONTO_ID = :P_CS_ID
  WHERE (JC.J_ID = :P_J_ID);
  
  IF(:P_FIRM_ID = 2)THEN
    BEGIN
    UPDATE TABL$J_1000016 JC SET
       JC.PAYSRC_ID  = 1000106
    WHERE (JC.J_ID = :P_J_ID);
    END

  UPDATE TABL$J_4 JC SET JC.FLAG_COMMIT = 1 WHERE (JC.ID = :P_J_ID);

  SUSPEND;
END
