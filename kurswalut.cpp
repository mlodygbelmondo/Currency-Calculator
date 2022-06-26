//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include <string>
#pragma hdrstop

#include "kurswalut.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
bool kontrolatekstu=0;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------




void __fastcall TForm4::Button1Click(TObject *Sender)
{
	/*
	AnsiString part1="/convert?from=";
	AnsiString resource1=part1+Kraj1;
	AnsiString part2="&&to=";
	resource1=resource1+part2; resource1=resource1+Kraj2;
	resource1=resource1+"&amount=1";  */
	TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
	TForm4::Button2Click(Button2);



}
//---------------------------------------------------------------------------

void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
	if (kwota2->Text!="")
	{
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm4::konwersja(AnsiString KRAJ1, AnsiString KRAJ2, AnsiString DLUGOSC)
{

	try
	{
		if(EUR->Caption!=PLN->Caption)
		{
			AnsiString resource1="/convert?from=USD&to=EUR&amount=1";
			resource1[15]=KRAJ1[1]; resource1[16]=KRAJ1[2]; resource1[17]=KRAJ1[3];
			resource1[22]=KRAJ2[1]; resource1[23]=KRAJ2[2]; resource1[24]=KRAJ2[3];
			Label3->Caption=resource1;
			RESTRequest1->Resource = resource1;
			RESTRequest1->Method   = TRESTRequestMethod::rmGET;
			RESTRequest1->Response = RESTResponse1;
			RESTRequest1->Response->ContentType = "application/json";
			RESTRequest1->Response->ContentEncoding="UTF-8";
			RESTRequest1->Execute();


			//AnsiString change = "";
			TJSONValue *jValue = RESTResponse1->JSONValue;
			Label5->Caption = jValue->ToString();
			AnsiString str_temp = Label5->Caption;
			int temp_val = str_temp.AnsiPos("result");
			Memo1->Lines->Add(temp_val);
			AnsiString str_temp2 = Label6->Caption;
			for (int i=0;i<6;i++)
			{
				str_temp2[1+i] = str_temp[temp_val+i+8];
			}
			Label6->Caption = TForm4::KropkaNaPrzecinek(str_temp2);
			Kurs->Caption = Label6->Caption;
			/*
			Memo1->Lines->Add(jValue->ToString());
			AnsiString str_temp = Memo1->Lines->Strings[35];
			Memo1->Lines->Clear();
			str_temp.SetLength(7);
			str_temp=TForm4::KropkaNaPrzecinek(str_temp);
			float temp=StrToFloat(str_temp);
			str_temp=FloatToStrF(temp, ffFixed, 5,4);

			Memo1->Lines->Add(str_temp);
			Kurs->Caption=str_temp;
			*/
		}
		else
		{
			AnsiString str_temp="1,000";
			Kurs->Caption=str_temp;
		}
		//Button1->Enabled=False;
	}
	catch(...)
	{
		Application->MessageBox(L"SprawdŸ swoje po³¹czenie internetowe i spróbuj ponownie.",
			L"Brak po³¹czenia z sieci¹", MB_OK | MB_ICONERROR);
	}
}
/*
void __fastcall TForm4::konwersja(AnsiString KRAJ1, AnsiString KRAJ2, AnsiString DLUGOSC)
{
	if(EUR->Caption!=PLN->Caption)
	{
	AnsiString resource1="/convert?from=USD&to=EUR&amount=1";
	resource1[15]=KRAJ1[1]; resource1[16]=KRAJ1[2]; resource1[17]=KRAJ1[3];
	resource1[22]=KRAJ2[1]; resource1[23]=KRAJ2[2]; resource1[24]=KRAJ2[3];
	Label3->Caption=resource1;
	RESTRequest1->Resource = resource1;
	RESTRequest1->Method   = TRESTRequestMethod::rmGET;
	RESTRequest1->Response = RESTResponse1;
	RESTRequest1->Response->ContentType = "application/json";
	RESTRequest1->Response->ContentEncoding="UTF-8";
	RESTRequest1->Execute();


	AnsiString change = "";
	TJSONValue *jValue = RESTResponse1->JSONValue;
	Label5->Caption = jValue->ToString();
	AnsiString str_temp = Label5->Caption;
	int temp_val = str_temp.AnsiPos("result");
	Memo1->Lines->Add(temp_val);
	AnsiString str_temp2 = Label6->Caption;
	for (int i=0;i<6;i++)
	{
		str_temp2[1+i] = str_temp[temp_val+i+8];
	}
	Label6->Caption = TForm4::KropkaNaPrzecinek(str_temp2);
	Kurs->Caption = Label6->Caption;
	}
	else
	{
		AnsiString str_temp="1,000";
		Kurs->Caption=str_temp;
	}
	//Button1->Enabled=False;
}
*/
AnsiString __fastcall TForm4::KropkaNaPrzecinek(AnsiString WARTOSC1)
	{
		for(int i=WARTOSC1.Length();i>0;i--)
		{
			if(WARTOSC1[i]=='.')
			WARTOSC1[i]=',';
		}
		return WARTOSC1;
	}
void __fastcall TForm4::Button2Click(TObject *Sender)
{
	float IloscWalutyDoKonwersji, WartoscKursuDoKonwersji, PoliczonaKwota;
	AnsiString tempDlaIlosciWaluty;
	WartoscKursuDoKonwersji=StrToFloat(Kurs->Caption);
	AnsiString temp2;
	if (kwota2->Text=="")
	{
		tempDlaIlosciWaluty="0";
		temp2="0";
	}
	else
	{
		tempDlaIlosciWaluty=kwota2->Text;
		temp2=kwota2->Text;
	}

	try
	{
		tempDlaIlosciWaluty=TForm4::KropkaNaPrzecinek(tempDlaIlosciWaluty);
		IloscWalutyDoKonwersji=StrToFloat(tempDlaIlosciWaluty);
		PoliczonaKwota=WartoscKursuDoKonwersji*IloscWalutyDoKonwersji;
		WartoscKonwersji->Caption=FloatToStr(PoliczonaKwota);
		WartoscKonwersji->Caption=FloatToStrF(PoliczonaKwota, ffFixed, 17,2);
		temp2=TForm4::KropkaNaPrzecinek(temp2);
		float temp=StrToFloat(temp2);
		temp2=FloatToStrF(temp, ffFixed, 17,2);
		kwota2->Text=temp2;
	}

	catch(...)
	{
		if(Application->MessageBox(L"SprawdŸ czy na pewno poda³eœ liczbê w prawid³iwym formacie!",
			L"Uwaga!", MB_OK | MB_ICONERROR) == IDOK )
			{
			   kwota2->Text="1,00";
			}
	}

}
//---------------------------------------------------------------------------


void __fastcall TForm4::EURMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
PopupMenu1->Popup(Form4->Left+X+115, Form4->Top+Y+155);
}
//---------------------------------------------------------------------------











void __fastcall TForm4::EURPOPClick(TObject *Sender)
{
	if(EUR->Caption!="EUR")
	{
		EUR->Caption="EUR";
		EUR2->Caption="EUR";
		podEUR->Caption="Euro";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::USDPOPClick(TObject *Sender)
{
	if(EUR->Caption!="USD")
	{
		EUR->Caption="USD";
		EUR2->Caption="USD";
		podEUR->Caption="Dolar amerykañski";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);

	}
}
//---------------------------------------------------------------------------



void __fastcall TForm4::PLNPOPClick(TObject *Sender)
{
	if(EUR->Caption!="PLN")
	{
		EUR->Caption="PLN";
		EUR2->Caption="PLN";
		podEUR->Caption="Z³oty";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::GBPPOPClick(TObject *Sender)
{
	if(EUR->Caption!="GBP")
	{
		EUR->Caption="GBP";
		EUR2->Caption="GBP";
		podEUR->Caption="Funt brytyjski";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::CHFPOPClick(TObject *Sender)
{
		EUR->Caption="CHF";
		EUR2->Caption="CHF";
		podEUR->Caption="Frank szwajcarski";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::CZKPOPClick(TObject *Sender)
{
		EUR->Caption="CZK";
		EUR2->Caption="CZK";
		podEUR->Caption="Korona Czeska";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::AUDPOPClick(TObject *Sender)
{
		EUR->Caption="AUD";
		EUR2->Caption="AUD";
		podEUR->Caption="Dolar australijski";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::CADPOPClick(TObject *Sender)
{
		EUR->Caption="CAD";
		EUR2->Caption="CAD";
		podEUR->Caption="Dolar kanadyjski";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::UAHPOPClick(TObject *Sender)
{
		EUR->Caption="UAH";
		EUR2->Caption="UAH";
		podEUR->Caption="Hryna ukraiñska";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::HRKPOPClick(TObject *Sender)
{
		EUR->Caption="HRK";
		EUR2->Caption="HRK";
		podEUR->Caption="Kuna chorwacka";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::EURPOP2Click(TObject *Sender)
{
	if(PLN->Caption!="EUR")
	{
		PLN->Caption="EUR";
		PLN2->Caption="EUR";
		podPLN->Caption="Euro";
		Button1->Enabled=True;
        		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::USDPOP2Click(TObject *Sender)
{
	if(PLN->Caption!="USD")
	{
		PLN->Caption="USD";
		PLN2->Caption="USD";
		podPLN->Caption="Dolar amerykañski";
		Button1->Enabled=True;
        		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm4::PLNPOP2Click(TObject *Sender)
{
	if(PLN->Caption!="PLN")
	{
		PLN->Caption="PLN";
		PLN2->Caption="PLN";
		podPLN->Caption="Z³oty";
		Button1->Enabled=True;
        		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::GBPPOP2Click(TObject *Sender)
{
	if(PLN->Caption!="GBP")
	{
		PLN->Caption="GBP";
		PLN2->Caption="GBP";
		podPLN->Caption="Funt brytyjski";
		Button1->Enabled=True;
        		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm4::CHFPOP2Click(TObject *Sender)
{
		PLN->Caption="CHF";
		PLN2->Caption="CHF";
		podPLN->Caption="Frank szwajcarski";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::CZKPOP2Click(TObject *Sender)
{
		PLN->Caption="CZK";
		PLN2->Caption="CZK";
		podPLN->Caption="Korona Czeska";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::AUDPOP2Click(TObject *Sender)
{
		PLN->Caption="AUD";
		PLN2->Caption="AUD";
		podPLN->Caption="Dolar australijski";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::CADPOP2Click(TObject *Sender)
{
		PLN->Caption="CAD";
		PLN2->Caption="CAD";
		podPLN->Caption="Dolar kanadyjski";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::UAHPOP2Click(TObject *Sender)
{
		PLN->Caption="UAH";
		PLN2->Caption="UAH";
		podPLN->Caption="Hryna ukraiñska";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::HRKPOP2Click(TObject *Sender)
{
		PLN->Caption="HRK";
		PLN2->Caption="HRK";
		podPLN->Caption="Kuna chorwacka";
		Button1->Enabled=True;
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------



void __fastcall TForm4::PLNMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	PopupMenu2->Popup(Form4->Left+X+491, Form4->Top+Y+155);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormCreate(TObject *Sender)
{
	TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
	TForm4::Button2Click(Button2);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormClose(TObject *Sender, TCloseAction &Action)
{
    Application->Terminate();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TForm4::kwota2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	/*

	*/
	if(Shift.Contains(ssCtrl))
		{
			AnsiString starytekst=kwota2->Text;
			if((Key==L'A')||(Key==L'a'))
			{
				kwota2->SelectAll();
				kontrolatekstu=1;
				//ShowMessage("Mo¿na wpisywaæ tylko liczby.");
			}
			else if((Key==L'x')||(Key==L'X')||(Key==L'c')||(Key==L'C'))
			{
				kontrolatekstu=1;
			}
			/*
			else if((Key==L'v')||(Key==L'V'))
			{
				kontrolatekstu=1;
				int temp=kwota2->Text.Length();

				for(int i=temp;i>0;i--)
					{
						if((kwota2->Text[i]!=L'.')& (kwota2->Text[i]!=L',') & (kwota2->Text[i]!=8) & (kwota2->Text[i]!=L'0') & (kwota2->Text[i]!=L'1') & (kwota2->Text[i]!=L'2')&(kwota2->Text[i]!=L'3') & (kwota2->Text[i]!=L'4') & (kwota2->Text[i]!=L'5')& (kwota2->Text[i]!=L'6') & (kwota2->Text[i]!=L'7') &(kwota2->Text[i]!=L'8') & (kwota2->Text[i]!=L'9'))
						{
							Application->MessageBox(L"Mo¿na wpisywaæ tylko liczby.",
							L"Ostrze¿enie!",	MB_OK | MB_ICONERROR);
							kwota2->Text=starytekst;
						}
					}
			}
            */
		}


}


void __fastcall TForm4::kwota2KeyPress(TObject *Sender, System::WideChar &Key)
{

	if(Key==13)
	{
		TForm4::konwersja(EUR->Caption,PLN->Caption,"1");
		TForm4::Button2Click(Button2);
	}
	/*if((Key!=L'.') & (Key!=L',') & (Key!=8) & (Key!=L'0') & (Key!=L'1') & (Key!=L'2')&(Key!=L'3') & (Key!=L'4') & (Key!=L'5')& (Key!=L'6') & (Key!=L'7') &(Key!=L'8') & (Key!=L'9') & (Key!=13))
		{
			if(kontrolatekstu==0)
			{
				Application->MessageBox(L"Mo¿na wpisywaæ tylko liczby.",
				L"Ostrze¿enie",	MB_OK | MB_ICONERROR);
				Key=0;
			}

		}    */
	kontrolatekstu=0;




}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

/*
void __fastcall TEdytor::TrescKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Shift.Contains(ssCtrl))
	{
		if(Key == 's' || Key=='S')
		{
			Edytor->Otwrz2Click(MainMenu1);
		}
		if(Key == 'n' || Key=='N')
		{
			Edytor->Nowy1Click(MainMenu1);
		}
		if(Key == 'O' || Key=='O')
		{
			Edytor->Otwrz1Click(MainMenu1);
		}
	}
} */



