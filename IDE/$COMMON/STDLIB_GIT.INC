{$DEFINE PEAKTOP:IDE/$COMMON/STDLIB_GIT.INC}
{$IFNDEF PEAKTOP:OBJ/TMEMO.INC}                         {$I PEAKTOP:OBJ/TMEMO.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                        {$I PEAKTOP:OBJ/TLABEL.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:APPL/CONSOLE/CAPTURED_WINDOWS.INC}     {$I PEAKTOP:APPL/CONSOLE/CAPTURED_WINDOWS.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}            {$I PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}        {$ENDIF}
  //================== PEAKTOP:IDE/$COMMON/STDLIB_GIT.INC ======================
const
  obj_name_common_memo        = 'Memo';
  obj_name_act_updaterun      = 'actUpdateRun';
  obj_name_act_updatecommit   = 'actUpdateCommit';
  obj_name_act_updatepush     = 'actUpdatePush';
  mgs_library_updates_caption = 'Обновления';
  //============================================================================
  function  TStdLibGit_InputQueryStr(const ACaption, aPrompt:string; var aValue:string):Boolean;
  var
    lkForm :TForm;
    lkMemo :TMemo;
  begin
    lkForm := TCommonForm_Create(ACaption, aPrompt,'PEAKTOP:IMG/CONFIG/UPDATE0016X0016.ICO', 'PEAKTOP:IMG/CONFIG/UPDATE0032X0032.BMP', true, nil);
    with lkForm do
      begin
      Width := 480;
      Height:= 320;
      end;
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_common_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := $BFFF80 or $A0A0A0;
      Colors.HotTrackBorder := $BFFF80;
      Caption               := #$20#$20#$20#$20#$20#$20+aPrompt;
      end;  
    lkMemo := CreateTMemo(lkForm, lkForm, 'Memo', 0, 80, 200, 200, alClient);
    with lkMemo do
      begin
      Font.Name := 'Courier New';
      Font.Size := 10;
      Font.Style:= [fsBold];
      ScrollBars:= ssVertical;
      Text      := aValue;
      end;
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      aValue := lkMemo.Text;
    lkForm.Free;
  end;
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
      lkSL[i] := #$20#$20#$20#$20+lkSL[i];
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
    lkPath := ' pull';
    lkMemo.Text := lkMemo.Text +
      FormatDateTime('dd.mm.yyyy hh:nn:ss',Now)+': '+lkGit+lkPath+#13#10+
      TStdLibGit_RunCaptured(ExtractFilePath(Amunhotep.SourcePath), lkGit, lkPath)+#13#10+#13#10;
  end;
  //============================================================================
  procedure TStdLibGit_actUpdateCommit_OnExecute(Sender :TObject);
  var
    lkMemo     :TMemo;
    lkGit      :string;
    lkPath     :string;
    lkComment  :string;
    lkVerSrc   :string;
  begin
    lkComment := '';
    TStdLibGit_InputQueryStr('Commit', 'Добавьте коментарий к коммиту', lkComment);
    lkVerSrc := 
      '//=============================================================================='+#13#10+
      '// This file content is generated automatically.'+#13#10+ 
      '// Please, DO NOT to edit this file!'+#13#10+
      '//=============================================================================='+#13#10+
      '{$DEFINE PEAKTOP:VERSION.INC}'+#13#10+
      'const AmunhotepLibraryVersion = '''+FormatDateTime('yyyymmddhhnnss', Now)+''';'+#13#10;    
    StringsSaveToFile('PEAKTOP:VERSION.INC', lkVerSrc);
    lkMemo := TMemo(TComponent(Sender).Owner.FindComponent(obj_name_common_memo));
    if not TStdLibGit_GetGitPath(lkGit) then exit;
    ChDir(Amunhotep.SourcePath);
    lkPath := ' commit --all ';
    if(StrTrimAll(lkComment) <> '')then
      lkPath := lkPath +' -m "'+StrReplaceStr(lkComment, '"', '`')+'"';
    lkMemo.Text := lkMemo.Text +
      FormatDateTime('dd.mm.yyyy hh:nn:ss',Now)+': '+lkGit+lkPath+#13#10+
      TStdLibGit_RunCaptured(ExtractFilePath(Amunhotep.SourcePath), lkGit, lkPath)+#13#10+#13#10;
  end;
  //============================================================================
  procedure TStdLibGit_actUpdatePush_OnExecute(Sender :TObject);
  var
    lkMemo     :TMemo;
    lkGit      :string;
    lkPath     :string;
  begin
    lkMemo := TMemo(TComponent(Sender).Owner.FindComponent(obj_name_common_memo));
    if not TStdLibGit_GetGitPath(lkGit) then exit;
    ChDir(Amunhotep.SourcePath);
    lkPath := ' push "https://amunhotep:ljytwr051096@github.com/amunhotep/lib.git" "origin" master:master ';
    lkMemo.Text := lkMemo.Text +
      FormatDateTime('dd.mm.yyyy hh:nn:ss',Now)+': '+lkGit+lkPath+#13#10+
      TStdLibGit_RunCaptured(ExtractFilePath(Amunhotep.SourcePath), lkGit, lkPath)+#13#10+#13#10;
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
    if FileExists(StrAbsolutePath('../conf/amunhotep-peaktop.conf', Amunhotep.ExeName))then
      begin
      lkAct := TCommonForm_CreateAction2(Result,obj_name_act_updatecommit,'Commit','Commit Git'                     ,'',0,547,@TStdLibGit_actUpdateCommit_OnExecute,nil,lkToolBar, 60,nil);
      lkAct := TCommonForm_CreateAction2(Result,obj_name_act_updatepush  ,'Push'  ,'Push into "https://github.com/"','',0,192,@TStdLibGit_actUpdatePush_OnExecute  ,nil,lkToolBar, 60,nil);
      end;
  end;
