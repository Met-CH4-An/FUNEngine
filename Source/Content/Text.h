#ifndef TEXT__H
#define TEXT__H
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
////////////////////////////////////////////////////////////////
#include "FContent.h"
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////
#include <vector>

namespace FE {

	namespace CONTENT {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CText {

		public:

			bool isValid(void);
			void setData(char* data, size_t size);
			size_t getSymbol(char *word);
			void getUint(uint32_t *outData);
			void getFloat(float *data);
			void getFloat(char *word);
			size_t getToSupremum(char *word, char supremum);
			size_t getInfSup(char *word, char infimum, char supremum);
			void getWord(char *word);

		private:

			char*					m_Data = nullptr;
			size_t					m_Size = 0;
			uint32_t				m_ID = 0;
			//uint32_t				m_IDMax = 0;
			bool					m_Valid = true;
			std::vector<char>		m_Result;

		public:

		}; // class CText

	} // namespace CONTENT

} // namespace FE

#endif // TEXT__H