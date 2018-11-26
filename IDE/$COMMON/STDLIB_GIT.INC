{$DEFINE PEAKTOP:IDE/$COMMON/STDLIB_GIT.INC}
{$IFNDEF PEAKTOP:OBJ/TMEMO.INC}                         {$I PEAKTOP:OBJ/TMEMO.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                        {$I PEAKTOP:OBJ/TLABEL.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:APPL/CONSOLE/CAPTURED_WINDOWS.INC}     {$I PEAKTOP:APPL/CONSOLE/CAPTURED_WINDOWS.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}            {$I PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}        {$ENDIF}
  //================== PEAKTOP:IDE/$COMMON/STDLIB_GIT.INC ======================
const
  obj_name_common_memo        = 'Memo';
  obj_name_act_updaterun      = 'actUpdateRun';
  mgs_library_updates_caption = 'Обновления';
  //============================================================================
  function TStdLibGit_RunCaptured(const aWorkingDir, aExeFileName, aExeFileParams:string):string;
  var
    i    :Integer;
    lkSL :TStrings;
  begin
    {$IFDEF MSWINDOWS}
    Result := RunCaptured(aWorkingDir, aExeFileName, aExeFileParams);  
    {$ENDIF}
    lkSL := TStringList.Create;
    lkSL.Text := Result;
    for i:=0 to lkSL.Count-1 do
      lkSL[i] := #$20#$20#$20#$20#$20#$20#$20#$20+lkSL[i];
    Result := lkSL.Text;
    lkSL.Free;  
  end;
  //============================================================================
  function TStdLibGit_GetGitPath(var aExePath:string):Boolean;
  begin
    Result := false;
    aExePath := StrAbsolutePath('../../git/bin/git.exe', Amunhotep.ExeName);
    {$IFDEF MSWINDOWS}
    aExePath := StrReplaceStr(aExePath, '/', '\');
    {$ENDIF}
    if not FileExists(aExePath)then
      begin
      Dialogs.MessageDlg('Не найден Git-клиент, необходимый для обновления программы.', mtError, [mbOk]);
      exit;
      end;
    Result := true;  
  end;
  //============================================================================
  function TStdLibGit_GetUpdateURL(var aURL:string):Boolean;
  begin
    aURL   := 'https://github.com/amunhotep/lib.git';
    Result := True;
  end;
  //============================================================================
  procedure TStdLibGit_actUpdateRun_OnExecute(Sender :TObject);
  var
    lkMemo     :TMemo;
    lkGit      :string;
    lkUpdateURL:string;
    lkPath     :string;
  begin
    lkMemo := TMemo(TComponent(Sender).Owner.FindComponent(obj_name_common_memo));
    if not TStdLibGit_GetGitPath(lkGit) then exit;
    if not TStdLibGit_GetUpdateURL(lkUpdateURL)then exit;
    ChDir(Amunhotep.SourcePath);

    lkPath := ' pull';// "'+Amunhotep.SourcePath+'" ';
    lkMemo.Text := lkMemo.Text +
      FormatDateTime('dd.mm.yyyy hh:nn:ss',Now)+': Обновление библиотеки кода.'+#13#10+
      #$20#$20#$20#$20+lkGit+lkPath+#13#10+
      TStdLibGit_RunCaptured(ExtractFilePath(Amunhotep.SourcePath), lkGit, lkPath)+#13#10+#13#10;
  end;
  //============================================================================
  procedure TStdLibGit_actCommitSVN_OnExecute(Sender :TObject);
  var
    lkMemo     :TMemo;
  begin
    {
    lkMemo := TMemo(TComponent(Sender).Owner.FindComponent(obj_name_common_memo));
    lkMemo.Text := lkMemo.Text +AmunhotepStandardLibrary_CommitSVN+#13#10+#13#10;
    TStdLibGit_actUpdateRun_OnExecute(Sender);
    }
  end;
  //============================================================================
  function TStdLibGit_Create(const aModalForm:Boolean):TForm;
  var
    lkMemo   :TMemo;
    lkToolBar:TxcGradientPanelVista;
    lkAct    :TCustomAction;
  begin
    Result := TCommonForm_Create(mgs_library_updates_caption, mgs_library_updates_caption,'PEAKTOP:IMG/CONFIG/UPDATE0016X0016.ICO',
      'PEAKTOP:IMG/CONFIG/UPDATE0032X0032.BMP', aModalForm, @TCommonForm_OnClose);
    with TxcGradientPanelVista(Result.FindComponent(obj_name_common_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := $BFFF80 or $A0A0A0;
      Colors.HotTrackBorder := $BFFF80;
      end;  
    lkToolBar := CreateTxcGradientPanelVistaToolBar(Result, Result, 'ToolBar', '', alTop, 0,200,24,600, xbsRaized);  
    lkMemo := CreateTMemo(Result, Result, obj_name_common_memo, 0, 200, 200, 200, alClient);
    with lkMemo do
      begin
      Color     := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Color:= Amunhotep.MainForm.StyleManager.Colors.Window;
      Text      := '';
      Font.Size := 8;
      Font.Name := 'Fixedsys';
      Font.Style:= [];
      ScrollBars:= ssBoth;
      WordWrap  := true;
      end; 
    lkAct := TCommonForm_CreateAction2(Result,obj_name_act_updaterun,'Обновить','Обновить библиотеку кода из репозитария' ,'F9'     ,0, 93,@TStdLibGit_actUpdateRun_OnExecute,nil,lkToolBar, 80,nil);
//    if FileExists(StrAbsolutePath('../conf/amunhotep-peaktop.conf', Amunhotep.ExeName))then
//    lkAct := TCommonForm_CreateAction2(Result,'actCommitSVN'        ,'Commit'  ,'Commit SVN'                              ,''       ,0,143,@TStdLibGit_actCommitSVN_OnExecute,nil,lkToolBar, 60,nil);
  end;
