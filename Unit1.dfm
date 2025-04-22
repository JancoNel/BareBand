object frm_BareBand: Tfrm_BareBand
  Left = 0
  Top = 0
  Caption = 'BareBand'
  ClientHeight = 352
  ClientWidth = 608
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 304
    Top = 104
    Width = 34
    Height = 15
    Caption = 'Label1'
  end
  object btn_diagnose: TButton
    Left = 280
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Diagnose!'
    TabOrder = 0
    OnClick = btn_diagnoseClick
  end
  object RichEdit1: TRichEdit
    Left = 56
    Top = 88
    Width = 185
    Height = 89
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Lines.Strings = (
      'RichEdit1')
    ParentFont = False
    TabOrder = 1
  end
end
