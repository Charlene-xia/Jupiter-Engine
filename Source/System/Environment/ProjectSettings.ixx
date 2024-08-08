// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

export module jpt.ProjectSettings;

import jpt.Json;
import jpt.Json.Data;
import jpt.File.Path;
import jpt.File.Path.Utils;
import jpt.Optional;

export namespace jpt
{
	/** Get & Set config at File::FixDependencies("Assets/Config/Settings.json") */
	class ProjectSettings
	{
	private:
		JsonMap m_settings;

	public:
		static ProjectSettings& GetInstance();

		bool PreInit();

		template<typename T>
		bool TryGet(const String& key, T& value) const;

		const JsonMap& GetSettings() const { return m_settings; }
	};

	ProjectSettings& ProjectSettings::GetInstance()
	{
		static ProjectSettings instance;
		return instance;
	}

	bool ProjectSettings::PreInit()
	{
		const File::Path projectSettingsJson = File::FixDependencies("Assets/Config/Settings.json");
		if (Optional<JsonMap> settings = ReadJsonFile(projectSettingsJson))
		{
			m_settings = settings.Value();
			return true;
		}

		return false;
	}

	template<typename T>
	bool ProjectSettings::TryGet(const String& key, T& value) const
	{
		if (m_settings.Has(key))
		{
			value = m_settings[key].As<T>();
			return true;
		}

		return false;
	}
}