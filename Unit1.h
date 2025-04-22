//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_BareBand : public TForm
{
__published:	// IDE-managed Components
	TButton *btn_diagnose;
	TLabel *Label1;
	TRichEdit *RichEdit1;
	void __fastcall btn_diagnoseClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrm_BareBand(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_BareBand *frm_BareBand;
//---------------------------------------------------------------------------
#endif
