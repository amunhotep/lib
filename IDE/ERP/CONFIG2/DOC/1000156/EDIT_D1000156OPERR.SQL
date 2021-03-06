SELECT J_ID, ID, NAME, FLAG_DELETE, TMCOPER_ID, TMCOPER_KM, KM_DONE, KM, KM_GONE, KM_LEFT
      ,(SELECT FIRST 1 COALESCE(O.NAME, '')
        FROM   TABL$R_TMCOPER O
        WHERE  (O.ID = D.TMCOPER_ID)
        ) AS TMCOPER_NAME
FROM   TABL$D_1000156OPER D
WHERE  (D.ID = ?ID)
