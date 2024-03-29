EXECUTE BLOCK (
  Q_J_ID TYPE OF COLUMN TABL$J_4.ID = ?J_ID
) RETURNS (
  ITEM_I                 TYPE OF COLUMN TABL$D_1000014.ID,
  ID                     TYPE OF COLUMN TABL$D_1000014.ID,
  NAME                   TYPE OF COLUMN TABL$D_1000014.NAME,
  FLAG_DELETE            TYPE OF COLUMN TABL$D_1000014.FLAG_DELETE,
  J_ID                   TYPE OF COLUMN TABL$D_1000014.J_ID,
  TMC_ID                 TYPE OF COLUMN TABL$D_1000014.TMC_ID,
  TMC_LIST_ID            TYPE OF COLUMN TABL$R_TMC.TMC_LIST_ID,
  TMC_NAME               TYPE OF COLUMN TABL$R_TMC.NAME,
  TMC_NAME2              TYPE OF COLUMN TABL$R_TMC.NAME,
  TMC_ARTICLE            TYPE OF COLUMN TABL$R_TMC.ARTICLE,
  TMC_NUMSHOW            TYPE OF COLUMN TABL$R_TMC.NUMSHOW,
  TMC_BARCODE            TYPE OF COLUMN TABL$R_TMC.BARCODE,
  TMC_EDIZM_ID           TYPE OF COLUMN TABL$R_TMC.EDIZM_ID,
  EDIZM_NAME             TYPE OF COLUMN TABL$R_EDIZM.NAME,
  EDIZM_SHORT            TYPE OF COLUMN TABL$R_EDIZM.SHORT_NAME,
  TMC_GROUP_ID           TYPE OF COLUMN TABL$R_TMC.TMC_GROUP_ID,
  TMC_GROUP_NAME         TYPE OF COLUMN TABL$R_TMC_GROUP.NAME,
  COUNTRY_ID             TYPE OF COLUMN TABL$R_TMC.COUNTRY_ID,
  VALUTE_NAME            TYPE OF COLUMN TABL$R_COUNTRIES.VALUTE,
  PROBE                  TYPE OF COLUMN TABL$R_TMC.PROBE,
  LGTH                   TYPE OF COLUMN TABL$R_TMC.LGTH,
  DIAM                   TYPE OF COLUMN TABL$R_TMC.DIAM,
  MASSA                  TYPE OF COLUMN TABL$R_TMC.MASSA,
  MASSA_INS              TYPE OF COLUMN TABL$R_TMC.MASSA,
  MASSA_NETTO            TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO,
  PRICE                  TYPE OF COLUMN TABL$D_1000014.PRICE,
  QUANT                  TYPE OF COLUMN TABL$D_1000014.QUANT,
  WRK_ID                 TYPE OF COLUMN TABL$D_1000014.WRK_ID,
  WRK_NAME               TYPE OF COLUMN TABL$R_WRK.NAME,
  PRICE_TMC              TYPE OF COLUMN TABL$D_1000014.PRICE_TMC,
  TOTAL                  TYPE OF COLUMN TABL$D_1000014.PRICE,
  PCPRICE                TYPE OF COLUMN TABL$D_1000014.PRICE_TMC)
AS
BEGIN
  ITEM_I = 0;
  FOR
    SELECT DB.ID, DB.NAME, DB.FLAG_DELETE, DB.J_ID, DB.TMC_ID, TMC.NAME, TMC.NAME2, TMC.ARTICLE, TMC.NUMSHOW, TMC.BARCODE,
           TMC.TMC_LIST_ID,  TMC.EDIZM_ID, E.NAME, E.SHORT_NAME,
           TMC.TMC_GROUP_ID, TG.NAME, TMC.COUNTRY_ID,
           (SELECT FIRST 1 C.VALUTE FROM TABL$R_COUNTRIES C WHERE (C.ID = TMC.COUNTRY_ID)),
           TMC.PROBE, TMC.LGTH, TMC.DIAM, TMC.MASSA, (TMC.MASSA - TMC.MASSA_NETTO), TMC.MASSA_NETTO,
           DB.WRK_ID, (SELECT FIRST 1 W.NAME FROM TABL$R_WRK W WHERE(W.ID = DB.WRK_ID))AS WRK_NAME,
           DB.PRICE, DB.QUANT, DB.PRICE_TMC, (DB.PRICE * DB.QUANT) AS TOTAL
    FROM   TABL$D_1000014 DB
             LEFT OUTER JOIN TABL$R_TMC       TMC ON (TMC.ID  = DB.TMC_ID)
             LEFT OUTER JOIN TABL$R_EDIZM     E   ON (E.ID    = TMC.EDIZM_ID)
             LEFT OUTER JOIN TABL$R_TMC_GROUP TG  ON (TG.ID   = TMC.TMC_GROUP_ID)
    WHERE  (DB.J_ID = :Q_J_ID)
    INTO   :ID, :NAME, :FLAG_DELETE, :J_ID, :TMC_ID, :TMC_NAME, :TMC_NAME2, :TMC_ARTICLE, :TMC_NUMSHOW, :TMC_BARCODE,
           :TMC_LIST_ID, :TMC_EDIZM_ID, :EDIZM_NAME, :EDIZM_SHORT,
           :TMC_GROUP_ID, :TMC_GROUP_NAME, :COUNTRY_ID, :VALUTE_NAME, :PROBE, :LGTH, :DIAM,
           :MASSA, :MASSA_INS, :MASSA_NETTO, :WRK_ID, :WRK_NAME,
           :PRICE, :QUANT, :PRICE_TMC, :TOTAL
  DO
    BEGIN
    ITEM_I = :ITEM_I + 1;

    PCPRICE = 0;
    IF(:PRICE <> 0)THEN
      PCPRICE = (:PRICE_TMC * 100) / :PRICE - 100;

    SUSPEND;
    END
END
