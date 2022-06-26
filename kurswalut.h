//---------------------------------------------------------------------------

#ifndef kurswalutH
#define kurswalutH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.JumpList.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TLabel *EUR;
	TLabel *podEUR;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Kurs;
	TButton *Button1;
	TRESTRequest *RESTRequest1;
	TRESTClient *RESTClient1;
	TRESTResponse *RESTResponse1;
	TMemo *Memo1;
	TLabel *PLN;
	TLabel *podPLN;
	TLabel *Label7;
	TTimer *Timer1;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *EUR2;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *PLN2;
	TLabel *Label13;
	TMemo *kwota1;
	TLabel *WartoscKonwersji;
	TButton *Button2;
	TPopupMenu *PopupMenu1;
	TMenuItem *EURPOP;
	TMenuItem *USDPOP;
	TMenuItem *PLNPOP;
	TMenuItem *GBPPOP;
	TPopupMenu *PopupMenu2;
	TMenuItem *EURPOP2;
	TMenuItem *USDPOP2;
	TMenuItem *PLNPOP2;
	TMenuItem *GBPPOP2;
	TEdit *kwota2;
	TMenuItem *CHFPOP;
	TMenuItem *CZKPOP;
	TMenuItem *AUDPOP;
	TMenuItem *CADPOP;
	TMenuItem *UAHPOP;
	TMenuItem *HRKPOP;
	TMenuItem *CHFPOP2;
	TMenuItem *CZKPOP2;
	TMenuItem *AUDPOP2;
	TMenuItem *CADPOP2;
	TMenuItem *UAHPOP2;
	TMenuItem *HRKPOP2;
	TLabel *Label5;
	TLabel *Label6;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall konwersja(AnsiString KRAJ1, AnsiString KRAJ2, AnsiString DLUGOSC);
	void __fastcall Button2Click(TObject *Sender);
	AnsiString __fastcall KropkaNaPrzecinek(AnsiString WARTOSC1);
	void __fastcall EURMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall EURPOPClick(TObject *Sender);
	void __fastcall USDPOPClick(TObject *Sender);
	void __fastcall PLNPOPClick(TObject *Sender);
	void __fastcall GBPPOPClick(TObject *Sender);
	void __fastcall EURPOP2Click(TObject *Sender);
	void __fastcall USDPOP2Click(TObject *Sender);
	void __fastcall PLNPOP2Click(TObject *Sender);
	void __fastcall GBPPOP2Click(TObject *Sender);
	void __fastcall PLNMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall kwota2KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall kwota2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CHFPOPClick(TObject *Sender);
	void __fastcall CZKPOPClick(TObject *Sender);
	void __fastcall AUDPOPClick(TObject *Sender);
	void __fastcall CADPOPClick(TObject *Sender);
	void __fastcall UAHPOPClick(TObject *Sender);
	void __fastcall HRKPOPClick(TObject *Sender);
	void __fastcall CHFPOP2Click(TObject *Sender);
	void __fastcall CZKPOP2Click(TObject *Sender);
	void __fastcall AUDPOP2Click(TObject *Sender);
	void __fastcall CADPOP2Click(TObject *Sender);
	void __fastcall UAHPOP2Click(TObject *Sender);
	void __fastcall HRKPOP2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
