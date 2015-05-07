#include "stdafx.h"
#using <System.dll>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <conio.h>

using namespace System;
using namespace System::Diagnostics;
using namespace System::Threading;
using namespace System::Globalization;
//using namespace System::Configuration;

int main( int arg, char* argv[] )
{
  CultureInfo^ ci;
  ci = gcnew CultureInfo("pl-PL");

  Console::WriteLine( "Raport EventLog. (C) MSi2 2009" );
  Console::WriteLine( "------------------------------\n" );

  DateTime now;
  int miesiac = DateTime::Now.Month;
  int rok = DateTime::Now.Year;
  if ( arg > 1 )
    {
    miesiac = atoi( argv[1] );
    char *ptr;
    if ( ( ptr = strchr( argv[1], '.' ) ) != NULL )
      rok = atoi( ptr+1 );
    }

  int wEntry = 1;        // czy zapiaæ godziny pocz¹tku i koñca (wpisy w EventLog)
  int podsumTyg = 1;     // czy zapisywaæ podsumowanie tygodniowe 
  int nonStop = 0;       // czy przyj¹æ, ¿e ka¿dego dnia praca trwa od pierwszego zalogowania do ostatniego wylogowania non stop 

  char iniName[1000];
  strcpy( iniName, argv[0] );
  char *p = strchr( iniName, '.' );
  if ( p )
    strcpy( p, ".ini" );


  if( (_access( iniName, 0 )) == 0 )
    {
    wchar_t buf[4001] = L"";
    wchar_t *parametry = L"Parametry";
    wchar_t *przedzialy = L"Przedzia³y";
    wchar_t *miesiacPar = L"Miesi¹c";
    wchar_t *tygodniowoPar = L"Tygodniowo";
    wchar_t *nonStopPar = L"NonStop";

    // Convert to a wchar_t*
    size_t origsize = strlen(iniName) + 1;
    const size_t newsize = 2000;
    size_t convertedChars = 0;
    wchar_t iniWName[newsize];
    mbstowcs_s(&convertedChars, iniWName, origsize, iniName, _TRUNCATE);
//    wcscat_s(wcstring, L" (wchar_t *)");
//    wcout << wcstring << endl;

    DWORD ret;
    ret = GetPrivateProfileString( parametry, przedzialy, L"", buf, 100, iniWName );
    if ( ret )
      wEntry = _wtoi( buf );
    ret = GetPrivateProfileString( parametry, tygodniowoPar, L"", buf, 100, iniWName );
    if ( ret )
      podsumTyg = _wtoi( buf );
    ret = GetPrivateProfileString( parametry, nonStopPar, L"", buf, 100, iniWName );
    if ( ret )
      nonStop = _wtoi( buf );
    ret = GetPrivateProfileString( parametry, miesiacPar, L"", buf, 100, iniWName );
    if ( ret )
      {
      miesiac = _wtoi( buf );
      wchar_t *ptr;
      if ( ( ptr = wcschr( buf, L'.' ) ) != NULL )
        rok = _wtoi( ptr+1 );
      }
    }  

  
  // Get the current configuration file.
  //Configuration:: config; // = ConfigurationManager.OpenExeConfiguration
  ////        ConfigurationUserLevel.None) as Configuration;

  ////customSection = 
  ////    config.GetSection("CustomSection") as CustomSection;

  ////Console.WriteLine("Section name: {0}", 
  ////    customSection.SectionInformation.Name);


  
   //// Create the source, if it does not already exist.
   //if (  !EventLog::SourceExists( "MySource" ) )
   //{
   //   //An event log source should not be created and immediately used.
   //   //There is a latency time to enable the source, it should be created
   //   //prior to executing the application that uses the source.
   //   //Execute this sample a second time to use the new source.
   //   EventLog::CreateEventSource( "MySource", "MyNewLog" );
   //   Console::WriteLine( "CreatingEventSource" );
   //   // The source is created.  Exit the application to allow it to be registered.
   //   return 0;
   //}


   //// Create an EventLog instance and assign its source.
   //EventLog^ myLog = gcnew EventLog;
   //myLog->Source = "MySource";

   //// Write an informational entry to the event log.    
   //myLog->WriteEntry( "Writing to event log." );

   //array<EventLog^>^remoteEventLogs;
   //remoteEventLogs = EventLog::GetEventLogs();
   //Console::WriteLine( "Number of logs on computer: {0}", remoteEventLogs->Length );
   //System::Collections::IEnumerator^ myEnum = remoteEventLogs->GetEnumerator();
   //while ( myEnum->MoveNext() )
   //{
   //   EventLog^ log = safe_cast<EventLog^>(myEnum->Current);
   //   Console::WriteLine( "Log: {0}", log->Log );
   //}

  EventLog^ sysLog = gcnew EventLog( "System" );

  
  System::DateTime poczatekMiesiaca ( rok, miesiac, 1 );
  System::DateTime koniecMiesiaca = poczatekMiesiaca.AddMonths( 1 );

  //poczatekMiesiaca = System::DateTime::MinValue;


  Console::WriteLine( "Miesi¹c: {0}",  poczatekMiesiaca.ToString( "MMMM yyyy", ci ) );
  Console::WriteLine();


  System::Collections::IEnumerator^ myEnum1 = sysLog->Entries->GetEnumerator();

  int ilePoczatek = 0;
  int jestPoczatek = 0;
  int jestKoniec = 0;
  int dzien = 0;
  int ileDni = 0;
  int ileDniTyg = 0;
  int znaczPoczTyg = 0;
  System::DateTime poczatekDnia;
  System::DateTime poczatek;
  TimeSpan czasPracy;
  System::TimeSpan suma = TimeSpan::Zero;
  System::TimeSpan sumaTydzien = TimeSpan::Zero;


  while ( myEnum1->MoveNext() )
  {
    EventLogEntry^ entry = safe_cast<EventLogEntry^>(myEnum1->Current);
    if ( poczatekMiesiaca <= entry->TimeGenerated && entry->TimeGenerated < koniecMiesiaca )
      {
      if ( entry->Source == "EventLog" && (entry->EventID == 6005 || entry->EventID == 6006 ) )
        {
        if ( dzien != entry->TimeGenerated.Day )
          {
          // tu siê zaczyna nowy dzieñ
          if ( dzien )
            {
            // zapisz poprzedni
            Console::WriteLine( "{0}, {1}", poczatekDnia.ToString("ddd dd.MM", ci), czasPracy );
            if ( wEntry )
              Console::WriteLine();
            suma += czasPracy;
            sumaTydzien += czasPracy;
            ileDni++;
            ileDniTyg++;
            znaczPoczTyg = 0;
            }

          dzien = entry->TimeGenerated.Day;
          ilePoczatek = 0;
          jestPoczatek = 0;
          jestKoniec = 0;
          czasPracy = TimeSpan::Zero;
          poczatekDnia = entry->TimeGenerated;
          }
        if ( entry->EventID == 6005 )
          {
          ilePoczatek++; 
          if ( !jestPoczatek )
            poczatek = entry->TimeGenerated;
          jestPoczatek = 1;
          }
        if ( entry->EventID == 6006 )
          {
          jestKoniec = 1; 
          if ( jestPoczatek )
            if ( !nonStop )
              czasPracy += entry->TimeGenerated - poczatek;
            else
              czasPracy = entry->TimeGenerated - poczatekDnia;
          jestPoczatek = 0;
          }
        if ( ileDni && poczatekDnia.DayOfWeek == DayOfWeek::Monday && znaczPoczTyg == 0 )
          {
          // pocz¹tek tygodnia
          if ( podsumTyg )
            {
            TimeSpan roznica = sumaTydzien.Add( TimeSpan(- ileDniTyg * 8, 0, 0 ) );
            int minus = (roznica < TimeSpan::Zero);
            Console::WriteLine( "Tygodniowo: czas: {0:00}:{1:00}, ró¿nica: {4}{2:00}:{3:00}", 
                (int)sumaTydzien.TotalHours, sumaTydzien.Minutes,
                (int)abs( roznica.TotalHours ), abs(roznica.Minutes),
                (minus)? "-" : "+" );
            }

          Console::WriteLine();
          znaczPoczTyg = 1;
          sumaTydzien = TimeSpan::Zero;
          ileDniTyg = 0;
          }
        if ( wEntry )
          Console::WriteLine( "   {0}, {1}", entry->TimeGenerated.ToString("HH:mm:ss", ci), (entry->EventID==6005)? "pocz¹tek" : "koniec" );
        }
      }
   }
  if ( !jestKoniec && jestPoczatek && DateTime::Now.Date == poczatekDnia.Date )
    // bie¿¹cy dzieñ nie zakoñczony - obliczaj do teraz
    if ( !nonStop )
      czasPracy += DateTime::Now - poczatek;
    else
      czasPracy = DateTime::Now - poczatekDnia;

  // zapisz ostatni dzieñ
  Console::WriteLine( "{0}, {1:00}:{2:00}:{3:00}", poczatekDnia.ToString("ddd dd.MM", ci), czasPracy.Hours, czasPracy.Minutes, czasPracy.Seconds );

  suma += czasPracy;
  sumaTydzien += czasPracy;
  ileDni++;
  ileDniTyg++;

  if ( podsumTyg )
    {
    TimeSpan roznica = sumaTydzien.Add( TimeSpan(- ileDniTyg * 8, 0, 0 ) );
    int minus = (roznica < TimeSpan::Zero);
    Console::WriteLine( "Tygodniowo: czas: {0:00}:{1:00}, ró¿nica: {4}{2:00}:{3:00}", 
        (int)sumaTydzien.TotalHours, sumaTydzien.Minutes,
        (int)abs( roznica.TotalHours ), abs(roznica.Minutes),
        (minus)? "-" : "+" );
    }
  if ( wEntry )
    Console::WriteLine();

  // podsumowanie
  Console::WriteLine();
  TimeSpan roznica = suma.Add( TimeSpan(- ileDni * 8, 0, 0 ) );

  int minus = (roznica < TimeSpan::Zero);

  Console::WriteLine( "£¹cznie: dni: {0}, czas: {1:00}:{2:00}, norma: {3}, ró¿nica: {6}{4:00}:{5:00}", ileDni, 
    (int)suma.TotalHours, suma.Minutes, ileDni * 8,  
    (int)abs( roznica.TotalHours ), abs(roznica.Minutes),
    (minus)? "-" : "+" );

  _getch();

}

