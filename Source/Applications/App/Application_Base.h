// Copyright Jupiter Technologies, Inc. All Rights Reserved.

#pragma once

namespace jpt
{
	class Window_Base;
	class Framework_Base;
	class Renderer_Base;

	/** Base abstract class for applications.
		It holds window, renderer, audio, collision managers, etc.*/
	class Application_Base
	{
	protected:
		Window_Base* m_pWindow = nullptr;
		Framework_Base* m_pFramework = nullptr;
		bool m_shouldTerminate = false;

	public:
		virtual ~Application_Base() = default;
		static Application_Base* GetInstance();

		virtual bool PreInit();
		virtual bool Init() { return true; }
		virtual void Update();
		virtual void Terminate();

		void Run();
		void TerminateApp();

		virtual const char* GetName() const { return "Application_Base"; }

	protected:
		void PollInput() { }
		void Render()    { }
	};
}