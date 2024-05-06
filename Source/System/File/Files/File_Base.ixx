// Copyright Jupiter Technologies, Inc. All Rights Reserved.

module;

export module jpt.File_Base;

import jpt.FileEnums;
import jpt.FilePath;
import jpt.TypeDefs;

export namespace jpt
{
	/** Base file abstraction for all files. */
	class File_Base
	{
	private:
		FilePath m_filePath;

	public:
		virtual ~File_Base() = default;


	};
}