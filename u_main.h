//---------------------------------------------------------------------------

#ifndef u_mainH
#define u_mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_BareBand : public TForm
{
__published:	// IDE-managed Components
	TButton *btn_diagnose;
	TRichEdit *RichEdit1;
	TBitBtn *BitBtn1;
	TPanel *Label1;
	void __fastcall btn_diagnoseClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrm_BareBand(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_BareBand *frm_BareBand;
//---------------------------------------------------------------------------
#endif
