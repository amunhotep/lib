EXECUTE BLOCK (
  Q_FIRM_ID       TYPE OF COLUMN TABL$J_4.FIRM_ID = ?FIRM_ID
 ,Q_PARENT_DOC_ID TYPE OF COLUMN TABL$J_4.ID      = ?PARENT_DOC_ID
)RETURNS (
  J_ID       TYPE OF COLUMN TABL$J_4.ID
 ,DOCTYPE_ID TYPE OF COLUMN TABL$J_4.TYPE_ID
)
AS
  DECLARE VARIABLE P_TAX_ID   TYPE OF COLUMN TABL$J_1000014.TAX_ID;
  DECLARE VARIABLE P_CS_ID    TYPE OF COLUMN TABL$J_1000014.CS_ID;
  DECLARE VARIABLE P_PLACE_ID TYPE OF COLUMN TABL$J_1000014.PLACE_ID;
  DECLARE VARIABLE P_FLAG     TYPE OF COLUMN TABL$J_4.FLAG_COMMIT;
  DECLARE VARIABLE P_J_ID     TYPE OF COLUMN TABL$J_4.ID;
BEGIN
  DOCTYPE_ID = 1000142;

  SELECT FIRST 1 F.CS_ID
  FROM   TABL$R_FIRMS F
  WHERE  (F.ID = :Q_FIRM_ID)
  INTO   :P_CS_ID;

  SELECT FIRST 1 MIN(PL.ID) AS ID
  FROM   TABL$R_PLACES PL
  WHERE  (PL.FILIAL_ID = (SELECT FIRST 1 F.ID FROM PROC$R_FILIALS_DEFAULT F))
    AND  (PL.ACC_ID = 281)
  INTO   :P_PLACE_ID;

  P_TAX_ID = 1000008;
  SELECT FIRST 1 COALESCE(F.NDP_PAY, 0) FROM TABL$R_FIRMS F WHERE (F.ID = :Q_FIRM_ID) INTO :P_FLAG;
  IF(:P_FLAG = 1)THEN P_TAX_ID = 1000010;

  SELECT FIRST 1 P.J_ID FROM PROC$J_INS_4(:Q_FIRM_ID, :DOCTYPE_ID, NULL) P INTO :J_ID;

  INSERT INTO TABL$J_1000014 (J_ID, CS_ID, CS_ADDR_ID, PLACE_ID, TAX_ID, TO_PLACE_ID, WRK_ID, TMC_GRID_ID)
    VALUES (:J_ID, :P_CS_ID, 0, :P_PLACE_ID, :P_TAX_ID, 0, 0, 0);

  UPDATE OR INSERT INTO TABL$J_CHILDS(J_ID, J_CHILD_ID)
    VALUES(:Q_PARENT_DOC_ID, :J_ID)
    MATCHING(J_ID, J_CHILD_ID);

  SUSPEND;
END
