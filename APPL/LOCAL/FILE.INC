{$DEFINE PEAKTOP:APPL/LOCAL/FILE.INC}
{$IFNDEF PEAKTOP:APPL/LOCAL/PARAMS.INC} {$I PEAKTOP:APPL/LOCAL/PARAMS.INC}  {$ENDIF}          
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}  {$I PEAKTOP:GLOBAL_VARIABLES.INC}   {$ENDIF} 
  //================== PEAKTOP:APPL/LOCAL/FILE.INC =============================
  function AmunhotepLocalStrings(const aLocal, aFileName:string):TStringList;
  var
    lkLocal      :string;
    lkFileName   :string;
    lkMsgName    :string;
    lkMsgValue   :string;
    lkJSONLoader :TlkJSONstreamed;
    lkJSONObjRoot:TlkJSONbase;
    lkJSONListMsg:TlkJSONList;
    lkJSONObjMsg :TlkJSONObject;
    lkJSONList   :TlkJSONList;
    i, j         :Integer;
  begin
    Result            := TStringList.Create;
    Result.Duplicates := dupIgnore;
    Result.Sorted     := True;
    lkFileName := PrepareAbsoleteFileName(aFileName);
    if FileExists(lkFileName)then
      begin
      Dialogs.MessageDlg('File does not exists!'+#13#10+lkFileName, mtError, [mbOK]);
      exit;
      end;
    lkLocal := aLocal;
    if(StrTrimAll(aLocal) = '')then 
      lkLocal := '1000054'; 
    try
      lkJSONLoader  := TlkJSONstreamed.Create;
      lkJSONObjRoot := lkJSONLoader.LoadFromFile( lkFileName );
    finally  
      lkJSONLoader.Free;
    end;  
    lkJSONListMsg := TlkJSONList( TlkJSONobjectmethod( TlkJSONObject(lkJSONObjRoot).Child[0] ).ObjValue );
    for i:=0 to lkJSONListMsg.Count-1 do
      begin
      lkJSONObjMsg := TlkJSONObject( lkJSONListMsg.Child[i] );
      lkMsgName    := lkJSONObjMsg.Field[AmunhotepLocalizeParamName].Value;
      lkJSONList   := TlkJSONList( lkJSONObjMsg.Field[AmunhotepLocalizeParamCaption] );
      
      end;
    lkJSONObjRoot.Free;  
  end;
