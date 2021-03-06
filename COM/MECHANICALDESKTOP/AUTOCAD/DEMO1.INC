{ **** UBPFD *********** by kladovka.net.ru ****
>> ��������� �������� ������� �� AutoCAD � ������� DXF

������� ����������� ��������� ����� �� AutoCAD � ������� DXF � ���������� ���������� ������ � ������ List. � ������ ��������� ���������� ������� ���������� True. � ������ ������ (AutoCAD �� ��������, c��� OLE � ����.) ������� ���������� False �� ����� ��������� � ������ �����

�����������: Windows, SysUtils, ComObj, ActiveX
�����:       Dimka Maslov, mainbox@endimus.ru, ICQ:148442121, �����-���������
Copyright:   Dimka Maslov
����:        22 ������ 2002 �.
********************************************** }

const
 Ext = 'dxf';
 DotExt = '.'+Ext;

function GetAcadDXFText(List: TStrings): Boolean;
var
 TempDir, FileName: string;
 ClassID: TGUID;
 Unknown: IUnknown;
 Dispatch: IDispatch;
 App, Doc, Sel: Variant;
 TempList: TStringList;
begin
 SetLength(TempDir, 1024{MAX_PATH});
 GetTempPath(MAX_PATH, PChar(TempDir));
 SetLength(TempDir, StrLen(@TempDir[1]));
 TempDir:=IncludeTrailingBackslash(TempDir);
 repeat
  FileName:=TempDir+IntToHex(LoWord(GetTickCount), 4)+DotExt;
 until not FileExists(FileName);
 SetLength(FileName, Length(FileName)-Length(DotExt));
 Result:=True;
 try
  ClassID := ProgIDToClassID('AutoCAD.Application');
  if not Succeeded(GetActiveObject(ClassID, nil, Unknown)) then Abort;
  Unknown.QueryInterface(IDispatch, Dispatch);
  App:=Dispatch;
  try
   Doc:=App.ActiveDocument;
   try
    Sel:=Doc.SelectionSets.Add('TEMP');
    try
     Doc.Export(FileName, Ext, Sel);
    finally
     Sel:=Unassigned;
    end;
   finally
    Doc:=Unassigned;
   end;
  finally
   App:=Unassigned;
  end;
  FileName:=FileName+DotExt;
  TempList:=TStringList.Create;
  try
   TempList.LoadFromFile(FileName);
   List.Assign(TempList);
  finally
   TempList.Free;
  end;
 except
  Result:=False;
 end;
 if FileExists(FileName) then DeleteFile(FileName);
end;

{usage}
if not GetAcadDXFText(Memo1.Lines) then
 ShowMessage('���������� �������� ������ �� AutoCAD');


//==============================================================================


