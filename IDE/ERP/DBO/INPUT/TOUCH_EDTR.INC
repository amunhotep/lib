{$DEFINE PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCALC.INC}                    {$I PEAKTOP:OBJ/TXCEDITCALC.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCOMBO.INC}                   {$I PEAKTOP:OBJ/TXCEDITCOMBO.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOMBOBOX.INC}                      {$I PEAKTOP:OBJ/TCOMBOBOX.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCSTDPANEL.INC}                    {$I PEAKTOP:OBJ/TXCSTDPANEL.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}               {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}          {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_MOUSE.INC} {$I PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_MOUSE.INC}{$ENDIF}
  //======================= PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC ===========
const
  OBJ_NAME_TOUCHEDTR_HEIGHT = 40;
  OBJ_NAME_TOUCHEDTR_NAME   = 'TouchEditorName';  
  OBJ_NAME_TOUCHEDTR_PARENT = 'TouchEditorParent';  
  //============================================================================
  function TTouchEditor_CreateTxcEditCalc(aOwner :TComponent; aParent:TWinControl; 
             const aName:string; const aLeft, aTop:Integer;
             const aIntegerOnly:Boolean; const aDecimalPlaces:Integer;
             const aValue:Extended):TxcEditCalc;
  var
    lkParent :TxcStdPanel;
  begin
    lkParent := CreateTxcStdPanel(aOwner, aParent, OBJ_NAME_TOUCHEDTR_PARENT, '', alNone, aLeft, aTop, OBJ_NAME_TOUCHEDTR_HEIGHT*9, OBJ_NAME_TOUCHEDTR_HEIGHT*6, xbsNone);
    Result   := CreateTxcEditCalc(aOwner, lkParent, aName, 1, 1, OBJ_NAME_TOUCHEDTR_HEIGHT, Trunc( (OBJ_NAME_TOUCHEDTR_HEIGHT*6) - 2) );
    with Result do
      begin
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style    := [fsBold];
      Font.Size     := 20;
      Alignment     := taRightJustify;
      if aIntegerOnly then
        begin
        DisplayFormat := '#0';
        DecimalPlaces := 0;
        end
      else 
        begin 
        DisplayFormat := '#0.###';
        DecimalPlaces := 3;
        end;
      Anchors       := [akLeft, akTop, akRight];
      Value         := aValue;
      end;
  
  end;
