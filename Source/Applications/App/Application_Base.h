// Copyright Jupiter Technologies, Inc. All Rights Reserved.

#pragma once

import jpt.Time.TypeDefs;

namespace jpt
{
	class Window_Base;
	class Framework_Base;
	class Renderer_Base;

	namespace Input
	{
		class Manager;
	}

	/** Base abstract class for applications.
		It holds window, renderer, audio, collision managers, etc.*/
	class Application_Base
	{
	protected:
		Framework_Base* m_pFramework    = nullptr;
		Window_Base*    m_pWindow       = nullptr;
		Renderer_Base*  m_pRenderer     = nullptr;

		Input::Manager* m_pInputManager = nullptr;

		bool m_shouldTerminate = false;

	public:
		virtual ~Application_Base() = default;

		virtual bool PreInit();
		virtual bool Init();
		virtual void Update(TimePrecision deltaSeconds);
		virtual void Terminate();

		void Run();
		void TerminateApp() { m_shouldTerminate = true; }

	protected:
		void ProcessInput();
		void Render();
	};
}