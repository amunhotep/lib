{$DEFINE PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC}
{$IFNDEF PEAKTOP:OBJ/TMASKEDIT.INC}                        {$I PEAKTOP:OBJ/TMASKEDIT.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCALC.INC}                      {$I PEAKTOP:OBJ/TXCEDITCALC.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCOMBO.INC}                     {$I PEAKTOP:OBJ/TXCEDITCOMBO.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOMBOBOX.INC}                        {$I PEAKTOP:OBJ/TCOMBOBOX.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCSTDPANEL.INC}                      {$I PEAKTOP:OBJ/TXCSTDPANEL.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                 {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}            {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_MOUSE.INC}   {$I PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_MOUSE.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_BUTTON.INC}  {$I PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_BUTTON.INC} {$ENDIF}
  //======================= PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC ===========
const
  OBJ_NAME_TOUCHEDTR_HEIGHT = 40;
  OBJ_NAME_TOUCHEDTR_NAME   = 'TouchEditorName';  
  OBJ_NAME_TOUCHEDTR_PARENT = 'TouchEditorParent';  
  //============================================================================
  procedure TTouchEditor_OnClick(Sender :TObject);
  begin
    with TMaskEdit( TComponent(Sender).Owner.FindComponent(OBJ_NAME_TOUCHEDTR_NAME) ) do
      begin
      if(SelLength > 0)then
        Text := '';
      if(Chr( TComponent(Sender).Tag ) = '<')then
        begin
        if(SelLength > 0)then
          Text := ''
         else 
          Text := Copy(Text, 1, Length(Text)-1);
        end 
      else
        begin
        if(Chr( TComponent(Sender).Tag ) = Copy(FormatFloat('#0.00',0),2,1) )then
          if(Length(Text) = 0)then
            Text := Text + '0';
        Text := Text + Chr( TComponent(Sender).Tag );
        end;
      SelLength := 0;
      SelStart  := Length(Text);  
      end;  
  end;
  //============================================================================
  function TTouchEditor_CreateTxcEditCalc(aOwner :TComponent; aParent:TWinControl; 
             const aLeft, aTop:Integer;
             const aIntegerOnly:Boolean; const aPasswordChar:Char;
             const aValue:Extended):TMaskEdit;
  var
    lkParent :TxcStdPanel;
    lkBtn    :TxcStdPanel;
    i        :Integer;
    lkSpec   :string;
  begin
    lkParent := CreateTxcStdPanel(aOwner, aParent, OBJ_NAME_TOUCHEDTR_PARENT, '', alNone, aLeft, aTop, OBJ_NAME_TOUCHEDTR_HEIGHT*9+8, OBJ_NAME_TOUCHEDTR_HEIGHT*6+2, xbsNone);
    lkParent.Color := Amunhotep.MainForm.StyleManager.Colors.Window;
    Result   := CreateTMaskEdit(lkParent, lkParent, OBJ_NAME_TOUCHEDTR_NAME, 1, 1, OBJ_NAME_TOUCHEDTR_HEIGHT, Trunc(OBJ_NAME_TOUCHEDTR_HEIGHT*6));
    with Result do
      begin
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style    := [fsBold];
      Font.Size     := 20;
      Anchors       := [akLeft, akTop, akRight];
      PasswordChar  := aPasswordChar;
      if aIntegerOnly then
        begin
        Text       := FormatFloat('#0', aValue);
        end
      else 
        begin 
        Text       := FormatFloat('#0.######', aValue);
        end;
      //Enabled       := False;  
      end;
    for i:=7 to 9 do
      TTouchEditor_CreateButton(lkParent, lkParent, 'btn'+IntToStr(i), IntToStr(i), IntToStr(i), '', '', alNone, taCenter, tlCenter, 
                 Trunc( (OBJ_NAME_TOUCHEDTR_HEIGHT*2 + 1) * (i-7) ), Trunc( (OBJ_NAME_TOUCHEDTR_HEIGHT+1) * 1), OBJ_NAME_TOUCHEDTR_HEIGHT*2, OBJ_NAME_TOUCHEDTR_HEIGHT*2, 
                 xbsNone, $F39621, @TTouchEditor_OnClick, true, 20).Tag := Ord( IntToStr(i)[1] );
    for i:=4 to 6 do
      TTouchEditor_CreateButton(lkParent, lkParent, 'btn'+IntToStr(i), IntToStr(i), IntToStr(i), '', '', alNone, taCenter, tlCenter, 
                 Trunc( (OBJ_NAME_TOUCHEDTR_HEIGHT*2 + 1) * (i-4) ), Trunc( (OBJ_NAME_TOUCHEDTR_HEIGHT+1) * 3), OBJ_NAME_TOUCHEDTR_HEIGHT*2, OBJ_NAME_TOUCHEDTR_HEIGHT*2, 
                 xbsNone, $F39621, @TTouchEditor_OnClick, true, 20).Tag := Ord( IntToStr(i)[1] );
    for i:=1 to 3 do
      TTouchEditor_CreateButton(lkParent, lkParent, 'btn'+IntToStr(i), IntToStr(i), IntToStr(i), '', '', alNone, taCenter, tlCenter, 
                 Trunc( (OBJ_NAME_TOUCHEDTR_HEIGHT*2 + 1) * (i-1) ), Trunc( (OBJ_NAME_TOUCHEDTR_HEIGHT+1) * 5), OBJ_NAME_TOUCHEDTR_HEIGHT*2, OBJ_NAME_TOUCHEDTR_HEIGHT*2, 
                 xbsNone, $F39621, @TTouchEditor_OnClick, true, 20).Tag := Ord( IntToStr(i)[1] );
    lkSpec := Copy(FormatFloat('#0.00', 0), 1, 2) + '<';
    for i:=1 to 3 do
      if not( (i = 2) and (aIntegerOnly) )then
      TTouchEditor_CreateButton(lkParent, lkParent, 'bts'+IntToStr(i), lkSpec[i], lkSpec[i], '', '', alNone, taCenter, tlCenter, 
                 Trunc( (OBJ_NAME_TOUCHEDTR_HEIGHT*2 + 1) * (i-1) ), Trunc( (OBJ_NAME_TOUCHEDTR_HEIGHT+1) * 7), OBJ_NAME_TOUCHEDTR_HEIGHT*2, OBJ_NAME_TOUCHEDTR_HEIGHT*2, 
                 xbsNone, $F39621, @TTouchEditor_OnClick, true, 20).Tag := Ord( lkSpec[i] );
  
  end;
