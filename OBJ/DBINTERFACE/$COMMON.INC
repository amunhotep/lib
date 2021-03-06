{$DEFINE PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}               {$I PEAKTOP:OBJ/TACTION.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                {$I PEAKTOP:OBJ/TLABEL.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$ENDIF}
const //================ PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC ===================
  msg_error_blobimpossible           = '���������� ��������� ������� ';
  msg_error_blobobjectisreadonly     = '������ �������� ������ ��� ������!';
  msg_error_loadtwainmodule          = '�� ������ ��������� ������ �������';
  msg_dbinterface_actload            = '�������';
  msg_dbinterface_actload_hint       = '��������� �� �������� �����';
  msg_dbinterface_actload2           = 'Web-������';
  msg_dbinterface_actload2_hint      = '��������� ����������� �� Web-������';
  msg_dbinterface_actload3           = '������';
  msg_dbinterface_actload3_hint      = '������������� ����������� � ���������';
  msg_dbinterface_actsave            = '���������';
  msg_dbinterface_actsave_hint       = '��������� �� ������� ����';
  msg_dbinterface_actcut             = '��������';
  msg_dbinterface_actcut_hint        = '�������� � ����� ������';
  msg_dbinterface_actcopy            = '����������';
  msg_dbinterface_actcopy_hint       = '���������� � ����� ������';
  msg_dbinterface_actpaste           = '��������';
  msg_dbinterface_actpaste_hint      = '�������� �� ������ ������';
  msg_dbinterface_actdelete          = '�������';
  msg_dbinterface_actdelete_hint     = '������� ���������� ��������';
  msg_dbinterface_actselectall       = '�������� ���';
  msg_dbinterface_actselectall_hint  = '�������� ���';
  //============================================================================
  function DBInterface_CreateTAction(aOwner :TComponent; aParent:TWinControl; 
             const aName, aCaption, aHint, aShortCut:string;
             const aGroupIndex, aImageIndex :Integer;
             aOnExecute, aOnUpdate :TNotifyEvent
             ):TCustomAction;
  var
    lkTBB      :TxcToolBarButton;
    lkLastLeft :Integer;
    i          :Integer; 
  begin
    Result := CreateTAction(aOwner, aName, aCaption, aHint, aShortCut, aGroupIndex, aImageIndex); 
    Result.OnExecute := aOnExecute; 
    Result.OnUpdate  := aOnUpdate; 
    lkLastLeft := 0;
    for i:=0 to aParent.ControlCount-1 do
      lkLastLeft := MaxInteger(lkLastLeft, aParent.Controls[i].Left + aParent.Controls[i].Width + 1);
    lkTBB := CreateTxcToolBarButton2(aParent, aParent, 'TBB'+Result.Name, lkLastLeft, 1, 22, 22, alLeft, Result);
  end;
  //============================================================================
  function DBInterface_CreateTAction2(aOwner :TComponent; aParent:TWinControl;
             const aWidth:Integer; const aShowCaption:Boolean; 
             const aName, aCaption, aHint, aShortCut:string;
             const aGroupIndex, aImageIndex :Integer;
             aOnExecute, aOnUpdate :TNotifyEvent
             ):TCustomAction;
  var
    lkTBB      :TxcToolBarButton;
    lkLastLeft :Integer;
    i          :Integer; 
  begin
    Result := CreateTAction(aOwner, aName, aCaption, aHint, aShortCut, aGroupIndex, aImageIndex); 
    Result.OnExecute := aOnExecute; 
    Result.OnUpdate  := aOnUpdate; 
    lkLastLeft := 0;
    for i:=0 to aParent.ControlCount-1 do
      lkLastLeft := MaxInteger(lkLastLeft, aParent.Controls[i].Left + aParent.Controls[i].Width + 1);
    lkTBB := CreateTxcToolBarButton2(aParent, aParent, 'TBB'+Result.Name, lkLastLeft, 1, 22, aWidth, alLeft, Result);
    lkTBB.ShowCaption := aShowCaption;
  end;  
