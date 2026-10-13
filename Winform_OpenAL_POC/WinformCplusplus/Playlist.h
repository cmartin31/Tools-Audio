#pragma once
#using <System.Web.Extensions.dll>

public ref class Playlist
{
public:
    property System::String^ Name;
    property System::Collections::Generic::List<System::String^>^ Tracks;

    Playlist()
    {
        Name = "";
        Tracks = gcnew System::Collections::Generic::List<System::String^>();
    }
};