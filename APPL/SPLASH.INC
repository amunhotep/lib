{$DEFINE PEAKTOP:APPL/SPLASH.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}{$I PEAKTOP:GLOBAL_VARIABLES.INC}{$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGE.INC}      {$I PEAKTOP:OBJ/TIMAGE.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}      {$I PEAKTOP:OBJ/TLABEL.INC}      {$ENDIF}
const //==================== PEAKTOP:APPL/SPLASH.INC ===========================
  amunhotep_splash_name        = 'AmunhotepSplashForm';
  amunhotep_splash_image_name  = 'ImageClient';
  amunhotep_splash_gauge_name  = 'Gauge';
  amunhotep_splash_label_big   = 'LabelBig';
  amunhotep_splash_label_small = 'LabelSmall';
  amunhotep_splash_indent      = 8;
  amunhotep_splash_rowheight   = 16;
  //============================================================================
  function Amunhotep_Splash_Create:TForm;
  var 
    lkCaption :string;
    lkFileName:string; 
    lkImg     :TImage;
    lkImgSave :TImage;
    lkLbl     :TLabel;
    lkGauge   :TxcGauge;
  begin 
    Result := TForm.Create(Amunhotep.MainForm);
    with Result do
      begin                    
      AlphaBlendValue := 232;
      AlphaBlend      := true;
      Name            := amunhotep_splash_name;
      ControlStyle    := ControlStyle + [csOpaque]; 
      Color           := clBlack;
      Position        := poScreenCenter;
      Height          := 361;
      Width           := 482;
      BorderStyle     := bsNone;
      Visible         := false;
      end;
    lkImg     := CreateTImage(Result,Result,amunhotep_splash_image_name,alClient,0,0,360,480);
    lkGauge := TxcGauge.Create(Result);
    with lkGauge do
      begin
      Name     := amunhotep_splash_gauge_name;
      Parent   := Result;
      Left     := amunhotep_splash_indent * 2;
      Top      := lkImg.Height - (amunhotep_splash_rowheight );
      Height   := amunhotep_splash_indent * 2;
      Width    := lkImg.Width  - (amunhotep_splash_indent * 4);
      Progress := 0;
      Visible  := false;
      StyleManager          := nil;
      Colors.Background     := $000000;
      Colors.Highlight      := $9F5F00;
      Colors.HotTrackBorder := $9F5F00;
      Colors.Foreground     := $FFBF00;
      Colors.Window         := $FFBF00;
      end;   
    lkLbl := CreateTLabel(Result, Result, ' ', lkGauge.Left, lkGauge.Top - (amunhotep_splash_rowheight + amunhotep_splash_indent)*3, amunhotep_splash_rowheight, lkGauge.Width, alNone, taLeftJustify);
    with lkLbl do
      begin
      Name       := amunhotep_splash_label_big;
      Font.Name  := 'Tahoma';
      Font.Size  := 10;
      Font.Color := $FFBF00;
      Font.Style := [fsBold];
      end;
    lkLbl := CreateTLabel(Result, Result, ' ', lkGauge.Left + (amunhotep_splash_indent * 2), lkGauge.Top - (amunhotep_splash_rowheight + amunhotep_splash_indent)*2, amunhotep_splash_rowheight, lkGauge.Width - (amunhotep_splash_indent * 2), alNone, taLeftJustify);
    with lkLbl do
      begin
      Name       := amunhotep_splash_label_small;
      Font.Name  := 'Fixedsys';
      Font.Size  := 12;
      Font.Color := $BF7F00;
      Font.Style := [];
      end;
    with lkImg do
      begin
      ControlStyle:= ControlStyle + [csOpaque]; 
      Center      := false;
      Transparent := false;
      lkFileName  := StrAbsolutePath('../conf/ent/splash.bmp', Amunhotep.ExeName);
      if FileExists(lkFileName)then
        Picture.Bitmap.LoadFromFile(lkFileName)
       else 
        begin
        lkFileName  := PrepareAbsoleteFileName('PEAKTOP:IMG/SPLASH/AMUNHOTEP4.BMP');
        if FileExists(lkFileName)then
          Picture.Bitmap.LoadFromFile(lkFileName)
         else
          with Picture.Bitmap.Canvas do
            begin
            Brush.Style := bsClear;
            Brush.Color := Result.Color;
            FillRect( Rect(0, 0, Result.Width-2, Result.Height - 1) ); 
            end; 
        end;  
      with Picture.Bitmap.Canvas do
        begin
        Brush.Style:= bsClear;
        Font.Name  := 'Tahoma';
        Font.Size  := 8;
        Font.Style := [fsBold];
        if(Pixels[0,0] = clBlack)then
          begin
          Font.Color := $FFBF00;
          TLabel(Result.FindComponent(amunhotep_splash_label_big)  ).Font.Color := $FFBF00;
          TLabel(Result.FindComponent(amunhotep_splash_label_small)).Font.Color := $BF7F00;
          end
         else
          begin
          Font.Color := $BF7F00;
          TLabel(Result.FindComponent(amunhotep_splash_label_big)  ).Font.Color := $BF7F00;
          TLabel(Result.FindComponent(amunhotep_splash_label_small)).Font.Color := $FFBF00;
          end;
        Brush.Style:= bsClear;
        lkCaption  := #$20#$A9+' ALOD software, 2002-'+FormatDateTime('yyyy', Now);
        TextOut(Trunc(amunhotep_splash_indent), Height - TextHeight('Wg') - Trunc(amunhotep_splash_indent) - 2, lkCaption);
        lkCaption  := 'version: ' + IntToStr(Trunc(Amunhotep.Version / 1000))+'.'+// major
          FormatFloat('0'   ,Trunc(Frac(Amunhotep.Version / 1000) *  10) )+'.'+ // minor
          FormatFloat('00'  ,     (Frac(Amunhotep.Version /  100) * 100) )+'.'+ // patch
          FormatFloat('0000',Amunhotep.Version)+' ';  
        TextOut(Width - TextWidth(lkCaption) - Trunc(amunhotep_splash_indent), Height - TextHeight('Wg') - Trunc(amunhotep_splash_indent) - 2, lkCaption);
        lkGauge.Top := Height - TextHeight('Wg') - amunhotep_splash_indent - lkGauge.Height;
        end;  
      end;
  end;
  //============================================================================
  function Amunhotep_Splash_Get:TForm;
  begin
    Result := nil;
    if(Amunhotep.MainForm.FindComponent(amunhotep_splash_name) = nil)then
      Result := Amunhotep_Splash_Create
     else
      Result := TForm(Amunhotep.MainForm.FindComponent(amunhotep_splash_name));
  end;
  //============================================================================
  procedure Amunhotep_Splash_Show;
  begin
    with Amunhotep_Splash_Get do
      if not Visible then
        begin
        Show;
        RePaint;
        Amunhotep.ProcessMessages;
        end;
  end;
  //============================================================================
  procedure Amunhotep_Splash_Hide;
  begin
    with Amunhotep_Splash_Get do
      if Visible then
        begin
        RePaint;
        Hide;
        Amunhotep.ProcessMessages;
        end;
  end;
  //============================================================================
  procedure Amunhotep_Splash_Free;
  begin
    with Amunhotep_Splash_Get do
      begin
      Free;
      Amunhotep.ProcessMessages;
      end;
  end;
  //============================================================================
  procedure Amunhotep_Splash_WriteLn(const aCaption:string);
  var
    lkForm :TForm;
  begin
    lkForm := Amunhotep_Splash_Get;
    TLabel(lkForm.FindComponent(amunhotep_splash_label_small)).Caption := aCaption;    
    lkForm.RePaint;  
    Amunhotep.ProcessMessages;
  end;
  //============================================================================
  procedure Amunhotep_Splash_OutText(const aCaption:string);
  var
    lkForm :TForm;
  begin
    lkForm := Amunhotep_Splash_Get;
    TLabel(lkForm.FindComponent(amunhotep_splash_label_big)).Caption := aCaption;    
    lkForm.RePaint;  
    Amunhotep.ProcessMessages;
  end;
  //============================================================================
  procedure Amunhotep_Splash_Progress_Set(const aCaption:string; const aProgress :Byte);
  var
    lkForm :TForm;
    lkGauge:TxcGauge;
  begin
    lkForm  := Amunhotep_Splash_Get;
    lkGauge := TxcGauge(lkForm.FindComponent(amunhotep_splash_gauge_name));
    with lkGauge do
      begin
      if not Visible then
        Visible := true;
      Progress := aProgress;
      end;
    lkForm.RePaint;  
    Amunhotep.ProcessMessages;
  end;
  //============================================================================
  procedure Amunhotep_Splash_Progress_Hide;
  var
    lkForm :TForm;
    lkGauge:TxcGauge;
  begin
    lkForm  := Amunhotep_Splash_Get;
    lkGauge := TxcGauge(lkForm.FindComponent(amunhotep_splash_gauge_name));
    with lkGauge do
      begin
      Visible := false;
      Progress := 0;
      end;
    lkForm.RePaint;  
    Amunhotep.ProcessMessages;
  end;
