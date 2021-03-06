EXECUTE BLOCK (
  Q_OBJ_ID TYPE OF COLUMN TABL$_IMG.OBJ_ID = ?OBJ_ID
 ,Q_REC_ID TYPE OF COLUMN TABL$_IMG.REC_ID = ?REC_ID
)RETURNS(
  OBJ_ID   TYPE OF COLUMN TABL$_IMG.OBJ_ID
 ,OBJ_TYPE TYPE OF COLUMN TABL$_IMG.ID
 ,OBJ_NAME TYPE OF COLUMN TABL$_IMG.NAME
 ,OBJ_PATH TYPE OF COLUMN TABL$_IMG.NAME
 ,REC_ID   TYPE OF COLUMN TABL$_IMG.REC_ID
 ,REC_NAME TYPE OF COLUMN TABL$_IMG.NAME
)AS
  DECLARE VARIABLE P_JRNL_ID  TYPE OF COLUMN TABL$_IMG.OBJ_ID;
  DECLARE VARIABLE P_OBJ_TYPE TYPE OF COLUMN TABL$_IMG.ID;
  DECLARE VARIABLE P_SQL      TYPE OF COLUMN TABL$_IMG.NAME;
BEGIN
  OBJ_ID   = :Q_OBJ_ID;
  REC_ID   = :Q_REC_ID;
  REC_NAME = '';

  SELECT FIRST 1 T.ID
  FROM   TABL$_TB T
  WHERE  (T.BASE_TYPE_ID = 4)
    AND  (T.TYPE_ID      = T.BASE_TYPE_ID)
    AND  (T.FLAG_MASTER  = 1)
  INTO   :P_JRNL_ID;

  SELECT FIRST 1 T.BASE_TYPE_ID, T.NAME, T.TYPE_ID
  FROM   TABL$_TB T
  WHERE  (T.ID = :Q_OBJ_ID)
  INTO   :OBJ_TYPE, :OBJ_NAME, :P_OBJ_TYPE;

  IF(:P_JRNL_ID = :OBJ_ID)THEN
    BEGIN
    SELECT FIRST 1 SUBSTRING(J.DOCSTR FROM 1 FOR 254)
    FROM   TABL$J_4 J
    WHERE  (J.ID = :REC_ID)
    INTO   :REC_NAME;
    END
   ELSE
    BEGIN
    IF(
         (EXISTS(SELECT R.RDB$RELATION_ID AS ID
                 FROM   RDB$RELATIONS R
                 WHERE  (TRIM(R.RDB$RELATION_NAME) = :OBJ_ID)
                 )
         )
       OR(EXISTS(SELECT P.RDB$PROCEDURE_ID AS ID
                 FROM   RDB$PROCEDURES P
                 WHERE  (TRIM(P.RDB$PROCEDURE_NAME) = :OBJ_ID)
                 )
          )
    )THEN
      BEGIN
      P_SQL = 'SELECT FIRST 1 T.NAME FROM '||:OBJ_ID||' T WHERE (T.ID = '''||:REC_ID||''')';
      EXECUTE STATEMENT :P_SQL INTO :REC_NAME;
      END
    END
  SUSPEND;
END
