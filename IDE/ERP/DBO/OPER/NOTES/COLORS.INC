{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/NOTES/COLORS.INC}
  //===================== PEAKTOP:IDE/ERP/DBO/OPER/NOTES/COLORS.INC ============
const OperNotesColors :array[0..5]of TColor;
  //============================================================================
  procedure OperNotesColorsInit;
  begin
    OperNotesColors[0] := $60BF00; 
    OperNotesColors[1] := $FF82C0; 
    OperNotesColors[2] := $8000FF;
    OperNotesColors[3] := $D5FFFF; 
    OperNotesColors[4] := $FFBF80; 
    OperNotesColors[5] := $BFBFBF;
  end;  
