{ 
**** UBPFD *********** by kladovka.net.ru ****
>> ���������� ��������� ����� ������� Interbase

���������� �� ������ ������� ��������� ������ VarChar � ���������
������ VarChar, ��������� ��� ���������� � ��������� ���� ���� Interbase.
�� ����������� �������!
����� ��������� (� ������) � ��������� ����� (� 2-������!) � ����� ���������
����� �������� �� ��������� � ������� ����������, �� �� ������� "And 127" � �����. 
��� ������ � Char �������� ����� �������� "Trim(S1);" � ����� ������.

�����������: Windows, SysUtils, DB
�����:       Vemer, Vemer@List.Ru, ������������
Copyright:   Vemer
����:        16 ������ 2003 �.
********************************************** }

  function CryptText( S1 :string; T:Boolean):string;
  var
    LS :Byte;//����� ������
    KB :Byte;//����, ����
    I  :Byte;//�������
    B  :Byte;//���� ������
    W  :Smallint;//����� ��� �����
    S2 :string;//���������
  begin
    LS := Length(S1);
    S2 := '';
    KB := LS * LS; //-------��������/���������!And 127 �� �������!
    if T = False Then // ����� ����� ����������� � �������������
      begin
      For I := 1 to LS Do
        begin //����������
        B:= Byte(S1[I]);
        If B > 32 Then
          begin
          W := B + KB;
          If W > 255 Then W := W - 223;
          B := W;
          end;//If
        S2 := S2 + Chr(B);
        KB := (KB + (I*2)) And 127; //-(1) ��������/���������! And 127 �� �������!
        end;//For
      end
     Else
      begin//����������
      For I := 1 to LS Do
        begin
        B:= Byte(S1[I]);
        If B > 32 Then
          begin
          W := B - KB;
          If W < 33 Then 
            W := W + 223;
          B := W;
          end;//If
        S2 := S2 + Chr(B);
        KB := (KB + (I*2)) And 127;//---(2) ������� ��� � (1)! And 127 �� �������!
        end;//For
      end;//Else
    Result := S2;
  end;
