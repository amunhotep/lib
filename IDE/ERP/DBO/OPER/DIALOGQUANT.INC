{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/DIALOGQUANT.INC}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                     {$I PEAKTOP:OBJ/TXCPANEL.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCSTDPANEL.INC}                  {$I PEAKTOP:OBJ/TXCSTDPANEL.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}      {$I PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/OPER/DIALOGQUANT.INC ===================
const ERP_OBJNAME_OPER_DLG_QUANT = 'DLG_QUANT';
  //============================================================================
  function ERPDialogQuant_Execute(const aCaption, aPrompt:string; const aIntegersOnly:Boolean; var aQuant:Extended):Boolean;
  var
    lkForm    :TForm;
    lkCntrl   :TWinControl;
    lkLbl     :TLabel;
    lkBtnOk   :TxcButton;
    lkBtnCn   :TxcButton;
    lkLastTop :Integer;
  begin
    Result := False;
    
    lkForm := TERPForm_Create(aCaption, ERP_ObjectIcon(ERP_OBJECTTYPE_OPER), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPER), true, nil);
    with lkForm do
      begin
      Position := poDesktopCenter;
      Width    := 480;
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

    lkBtnCn := CreateTxcButton(lkForm, lkForm, '', 'Отмена', lkForm.Width - 96, lkLastTop+160, 32, 88, mrCancel, False, True);
    with lkBtnCn do
      begin
      Font.Style    := [fsBold];
      Font.Size     := 12;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Anchors       := [akRight, akBottom];
      end;
    lkBtnOk := CreateTxcButton(lkForm, lkForm, '', 'OK'    , lkBtnCn.Left - 96, lkLastTop+160, 32, 88, mrOK    , True , False);
    with lkBtnOk do
      begin
      Font.Style    := [fsBold];
      Font.Size     := 12;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Anchors       := [akRight, akBottom];
      end;
    Result := (lkForm.ShowModal = mrOK);
    if Result then
      aQuant := 1;
    lkForm.Free;
  end;
