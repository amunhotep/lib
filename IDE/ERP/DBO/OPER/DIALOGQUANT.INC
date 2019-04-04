{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/DIALOGQUANT.INC}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                     {$I PEAKTOP:OBJ/TXCPANEL.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCSTDPANEL.INC}                  {$I PEAKTOP:OBJ/TXCSTDPANEL.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCBUTTON.INC}                     {$I PEAKTOP:OBJ/TXCBUTTON.INC}                         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}      {$I PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC}     {$I PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC}           {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/OPER/DIALOGQUANT.INC ===================
const ERP_OBJNAME_OPER_DLG_QUANT = 'DLG_QUANT';
  //============================================================================
  function ERPDialogQuant_Execute(const aCaption, aPrompt:string; const aIntegersOnly:Boolean; const aDecimalPlaces:Integer; var aQuant:Extended):Boolean;
  var
    lkForm    :TForm;
    lkCntrl   :TWinControl;
    lkLbl     :TLabel;
    lkEdtr    :TxcEditCalc;
    lkBtnOk   :TxcButton;
    lkBtnCn   :TxcButton;
    lkLastTop :Integer;
  begin
    Result := False;
    lkForm := TERPForm_Create(aCaption, ERP_ObjectIcon(ERP_OBJECTTYPE_OPER), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPER), true, nil);
    with lkForm do
      begin
      Position := poDesktopCenter;
      Width    := 360;
      Height   := 640;
      end; 
    lkLastTop := 0;             
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      lkLastTop := Top + Height;
      end;  
    lkLbl := CreateTLabel(lkForm, lkForm, aPrompt, 0, lkLastTop+1, 36, lkForm.Width, alTop, taLeftJustify);
    with lkLbl do
      begin
      Font.Style    := [fsBold];
      Font.Size     := 12;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      lkLastTop     := Top + Height;
      end;
    lkEdtr := TTouchEditor_CreateTxcEditCalc(lkForm, lkForm, OBJ_NAME_TOUCHEDTR_NAME, 0, lkLastTop+1, aIntegersOnly, aDecimalPlaces, aQuant);
    lkLastTop := lkLastTop + lkEdtr.Parent.Height + 1; 

    lkBtnCn := CreateTxcButton(lkForm, lkForm, '', 'Отмена', lkForm.Width - 96, lkLastTop+1, 32, 88, mrCancel, False, True);
    with lkBtnCn do
      begin
      Font.Style    := [fsBold];
      Font.Size     := 12;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Anchors       := [akRight, akBottom];
      end;
    lkBtnOk := CreateTxcButton(lkForm, lkForm, '', 'OK'    , lkForm.Width - (96*2), lkLastTop+1, 32, 88, mrOK    , True , False);
    with lkBtnOk do
      begin
      Font.Style    := [fsBold];
      Font.Size     := 12;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Anchors       := [akRight, akBottom];
      end;
    Result := (lkForm.ShowModal = mrOK);
    if Result then
      aQuant := lkEdtr.Value;
    lkForm.Free;
  end;
