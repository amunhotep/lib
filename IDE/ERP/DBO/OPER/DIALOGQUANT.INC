{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/DIALOGQUANT.INC}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                     {$I PEAKTOP:OBJ/TXCPANEL.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCSTDPANEL.INC}                  {$I PEAKTOP:OBJ/TXCSTDPANEL.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCBUTTON.INC}                     {$I PEAKTOP:OBJ/TXCBUTTON.INC}                         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}      {$I PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC}     {$I PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC}           {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/OPER/DIALOGQUANT.INC ===================
const ERP_OBJNAME_OPER_DLG_QUANT = 'DLG_QUANT';
  //============================================================================
  function ERPDialogQuant_Execute(const aCaption, aPrompt:string; const aIntegersOnly:Boolean; var aQuant:Extended):Boolean;
  var
    lkForm    :TForm;
    lkLbl     :TLabel;
    lkEdtr    :TMaskEdit;
    lkLastTop :Integer;
  begin
    Result := False;
    lkForm := TERPForm_Create(aCaption, ERP_ObjectIcon(ERP_OBJECTTYPE_OPER), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPER), true, nil);
    with lkForm do
      begin
      Position    := poDesktopCenter;
      Width       := OBJ_NAME_TOUCHEDTR_HEIGHT*6 + 8;
      Height      := OBJ_NAME_TOUCHEDTR_HEIGHT*11;
      BorderStyle := bsDialog;
      end; 
    lkLastTop := 0;             
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      lkLastTop             := Top + Height;
      end;  
    lkLbl := CreateTLabel(lkForm, lkForm, aPrompt, 0, lkLastTop+1, OBJ_NAME_TOUCHEDTR_HEIGHT*2, lkForm.Width, alTop, taLeftJustify);
    with lkLbl do
      begin
      Font.Style    := [fsBold];
      Font.Size     := 7;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      lkLastTop     := Top + Height;
      end;
    lkEdtr := TTouchEditor_CreateTxcEditCalc(lkForm, lkForm, 0, lkLastTop+1, aIntegersOnly, #0, aQuant);
    lkLastTop := lkLastTop + lkEdtr.Parent.Height; 

    lkForm.Height := lkLastTop + OBJ_NAME_TOUCHEDTR_HEIGHT;    
    Result := (lkForm.ShowModal = mrOK);
    if Result then
      aQuant := StrToFloat( StrReplaceStr(lkEdtr.Text, ',', '.') );
    lkForm.Free;
  end;
  //============================================================================
  function ERPDialogQuantInt_Execute(const aCaption, aPrompt:string; var aQuant:Integer):Boolean;
  var
    lkQuant :Extended;
  begin
    lkQuant := aQuant;
    Result := ERPDialogQuant_Execute(aCaption, aPrompt, True, lkQuant);
    if Result then
      aQuant := Trunc(lkQuant); 
  end;
  //============================================================================
  function ERPDialogPwd_Execute(const aCaption, aPrompt:string; var aValue:string):Boolean;
  var
    lkForm    :TForm;
    lkLbl     :TLabel;
    lkEdtr    :TMaskEdit;
    lkLastTop :Integer;
  begin
    Result := False;
    lkForm := TERPForm_Create(aCaption, ERP_ObjectIcon(ERP_OBJECTTYPE_OPER), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPER), true, nil);
    with lkForm do
      begin
      Position    := poDesktopCenter;
      Width       := OBJ_NAME_TOUCHEDTR_HEIGHT*6 + 8;
      Height      := OBJ_NAME_TOUCHEDTR_HEIGHT*11;
      BorderStyle := bsDialog;
      end; 
    lkLastTop := 0;             
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      lkLastTop             := Top + Height;
      end;  
    lkLbl := CreateTLabel(lkForm, lkForm, aPrompt, 0, lkLastTop+1, OBJ_NAME_TOUCHEDTR_HEIGHT*2, lkForm.Width, alTop, taLeftJustify);
    with lkLbl do
      begin
      Font.Style    := [fsBold];
      Font.Size     := 7;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      lkLastTop     := Top + Height;
      end;
    lkEdtr := TTouchEditor_CreateTxcEditCalc(lkForm, lkForm, 0, lkLastTop+1, True, '*', 0);
    lkEdtr.Text := aValue;
    lkLastTop := lkLastTop + lkEdtr.Parent.Height; 

    lkForm.Height := lkLastTop + OBJ_NAME_TOUCHEDTR_HEIGHT;    
    Result := (lkForm.ShowModal = mrOK);
    if Result then
      aValue := lkEdtr.Text;
    lkForm.Free;
  end;  
