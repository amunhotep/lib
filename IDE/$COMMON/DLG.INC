{$DEFINE PEAKTOP:IDE/$COMMON/DLG.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}              {$I PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}          {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}             {$I PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}        {$ENDIF}
  //========================== PEAKTOP:IDE/$COMMON/DLG.INC =====================
  function TDlg_Create(const aCaption, aPrompt, aIconFileName, aImageFileName:string; const aColor:TColor; const aWidth, aHeight:Integer):TForm;
  var
    lkBottomBar :TxcGradientPanelVista;
  begin
    Result := TCommonForm_Create(aCaption, aPrompt, aIconFileName, aImageFileName, True, nil);
    with Result do
      begin
      Width  := aWidth;
      Height := aHeight;
      end;
    with TxcGradientPanelVista( Result.FindComponent(obj_name_common_topbar) ) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := aColor or $A0A0A0;
      Colors.HotTrackBorder := aColor;
      Caption               := #$20#$20#$20#$20#$20#$20+aPrompt;
      end;  
  end;
  
