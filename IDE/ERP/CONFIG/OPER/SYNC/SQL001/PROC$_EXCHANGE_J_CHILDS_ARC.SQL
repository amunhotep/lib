CREATE OR ALTER PROCEDURE PROC$_EXCHANGE_J_CHILDS_ARC (
  Q_DATABASEPATH TYPE OF COLUMN TABL$R_FILIALS.DATABASE_NAME,
  Q_USERNAME     TYPE OF COLUMN TABL$_USERS.ID,
  Q_USERPWD      TYPE OF COLUMN TABL$_USERS.PWD,
  Q_FILIAL_ID    TYPE OF COLUMN TABL$R_FILIALS.ID,
  Q_J_ID         TYPE OF COLUMN TABL$J_4.ID)
RETURNS (
  TYPE_ID TYPE OF COLUMN TABL$_TB_TYPES.ID,
  NAME    TYPE OF COLUMN TABL$_TB.NAME,
  CNT     TYPE OF COLUMN TABL$J_4.ID)
AS
  DECLARE VARIABLE P_J_ID      TYPE OF COLUMN TABL$J_CHILDS.J_CHILD_ID;
  DECLARE VARIABLE P_NAME      TYPE OF COLUMN TABL$_TB.NAME;
  DECLARE VARIABLE P_SQL_STMT  TYPE OF COLUMN TABL$J_4.DOCSTR;
BEGIN
  TYPE_ID = 4;
  CNT     = 0;
  P_NAME  = '    +-- Зависимости документов TABL$J_CHILDS';
  P_SQL_STMT = 'SELECT JC.J_ID FROM TABL$J_CHILDS JC WHERE (JC.J_CHILD_ID = '||:Q_J_ID||') ORDER BY JC.J_ID ';
  FOR
    EXECUTE STATEMENT :P_SQL_STMT
      ON EXTERNAL DATA SOURCE :Q_DATABASEPATH AS USER :Q_USERNAME PASSWORD :Q_USERPWD
      WITH AUTONOMOUS TRANSACTION
    INTO :P_J_ID
  DO
    BEGIN
    UPDATE OR INSERT INTO TABL$J_CHILDS(J_ID, J_CHILD_ID)
      VALUES(:P_J_ID, :Q_J_ID)
      MATCHING(J_ID, J_CHILD_ID);
    NAME = :P_NAME ||' ('||:P_J_ID||','||:Q_J_ID||') ';
    CNT = :CNT + 1;
    SUSPEND;
    END
END
