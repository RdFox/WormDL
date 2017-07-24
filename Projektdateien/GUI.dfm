object F_Worm: TF_Worm
  Left = 118
  Top = 246
  Width = 416
  Height = 463
  Caption = 'WormDL 1.0'
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object L_Countdown: TLabel
    Left = 136
    Top = 136
    Width = 117
    Height = 106
    Caption = 'L_C'
    Color = clBtnFace
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = 'Segoe Script'
    Font.Style = [fsBold, fsItalic]
    ParentColor = False
    ParentFont = False
    ShowAccelChar = False
    Transparent = True
    Visible = False
  end
  object M_Exit: TLabel
    Left = 344
    Top = 392
    Width = 41
    Height = 26
    Caption = ' Exit '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    OnClick = M_ExitClick
  end
  object GM_Neu: TLabel
    Left = 256
    Top = 392
    Width = 72
    Height = 26
    Caption = 'Neustart '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    Visible = False
    OnClick = GM_NeuClick
  end
  object GM_Pause: TLabel
    Left = 8
    Top = 392
    Width = 55
    Height = 26
    Caption = ' Pause '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    Visible = False
    OnClick = GM_PauseClick
  end
  object GM_Weiter: TLabel
    Left = 72
    Top = 392
    Width = 62
    Height = 26
    Caption = ' Weiter '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    Visible = False
    OnClick = GM_WeiterClick
  end
  object L_Titel1: TLabel
    Left = 32
    Top = 16
    Width = 320
    Height = 47
    Caption = ' Willkommen im Reich '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object L_Titel2: TLabel
    Left = 96
    Top = 56
    Width = 191
    Height = 47
    Caption = ' der Würmer '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object L_MAnzahl: TLabel
    Left = 16
    Top = 120
    Width = 349
    Height = 28
    Caption = ' Wieviel Würmer sollen rekrutiert werden? '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object L_MGameMod: TLabel
    Left = 16
    Top = 264
    Width = 212
    Height = 28
    Caption = ' Wie soll gespielt werden? '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object L_EndPunkte0: TLabel
    Left = 32
    Top = 248
    Width = 141
    Height = 33
    Caption = 'L_EndPunkte0'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    Visible = False
  end
  object L_EndPunkte1: TLabel
    Left = 216
    Top = 248
    Width = 141
    Height = 33
    Caption = 'L_EndPunkte1'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    Visible = False
  end
  object L_GameOver: TLabel
    Left = 32
    Top = 144
    Width = 308
    Height = 85
    Caption = ' Game Over '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -48
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    Visible = False
  end
  object MM_WurmAnzahl: TRadioGroup
    Left = 40
    Top = 152
    Width = 209
    Height = 89
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ItemIndex = 0
    Items.Strings = (
      '1 Wurm    ~ 1 Spieler'
      '2 Würmer ~ 1 Spieler'
      '2 Würmer ~ 2 Spieler')
    ParentFont = False
    TabOrder = 0
  end
  object MM_GameMod: TRadioGroup
    Left = 40
    Top = 296
    Width = 209
    Height = 89
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ItemIndex = 0
    Items.Strings = (
      'Endlos'
      'Harte Wände'
      'Harte Würmer'
      'Alles Hart'
      'Chuck Norris Mode')
    ParentFont = False
    TabOrder = 1
  end
  object MM_IAnzahl: TButton
    Left = 264
    Top = 160
    Width = 73
    Height = 33
    Caption = 'Info'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    TabOrder = 2
    OnClick = MM_IAnzahlClick
  end
  object MM_IGameMod: TButton
    Left = 264
    Top = 304
    Width = 73
    Height = 33
    Caption = 'Info'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    TabOrder = 3
    OnClick = MM_IGameModClick
  end
  object MM_Start: TButton
    Left = 264
    Top = 344
    Width = 121
    Height = 33
    Caption = 'Starten'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe Print'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
    TabOrder = 4
    OnClick = MM_StartClick
  end
  object E_Punkte0: TEdit
    Left = 0
    Top = 0
    Width = 113
    Height = 21
    Enabled = False
    ReadOnly = True
    TabOrder = 5
    Text = 'Punkte'
    Visible = False
  end
  object E_Punkte1: TEdit
    Left = 280
    Top = 0
    Width = 113
    Height = 21
    Enabled = False
    ReadOnly = True
    TabOrder = 6
    Text = 'Punkte'
    Visible = False
  end
  object T_Timer1: TTimer
    Enabled = False
    Interval = 500
    OnTimer = T_Timer1Timer
    Left = 216
    Top = 392
  end
end
