namespace Creativengine {

	__declspec(dllimport) int Run(const char* version);

}

int main()
{
	Creativengine::Run("Version: 1.0");

	return 0;
}