////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "Text.h"
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для исключений
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////

namespace FE {

	namespace CONTENT {

		//==============================================================
		//==============================================================

		void CText::setData(char* data, size_t size) {

			if (data == nullptr || size == 0) m_Valid = false;

			else {

				m_Data = data;
				m_Size = size - 1;

			}

		}

		//==============================================================
		//==============================================================

		bool CText::isValid(void) { return m_Valid; }

		//==============================================================
		//==============================================================

		size_t CText::getSymbol(char *word) {

			size_t		_offset = m_ID;
			uint32_t	_idWord = 0;

			if (m_Valid) {

				char _symbol = m_Data[m_ID];

				word[_idWord++] = _symbol;

				if (m_ID < m_Size) ++m_ID;

				else m_Valid = false;

			}

			word[_idWord++] = 0;

			return m_ID - _offset;
		}

		//==============================================================
		//==============================================================

		void CText::getUint(uint32_t *outData) {

			char _symbol;

			while (m_Valid) {

				_symbol = m_Data[m_ID];

				if (_symbol > 0x2F && _symbol < 0x3A) break;

				if (m_ID < m_Size) ++m_ID;

				else m_Valid = false;
			}

			uint32_t _major = 0;

			while (m_Valid) {

				_symbol = m_Data[m_ID];

				if ((_symbol > 0x2F && _symbol < 0x3A) || _symbol == '.') {

					uint32_t _number = 0;
					switch (_symbol) {

					case '0': _number = 0;  break;
					case '1': _number = 1;  break;
					case '2': _number = 2;  break;
					case '3': _number = 3;  break;
					case '4': _number = 4;  break;
					case '5': _number = 5;  break;
					case '6': _number = 6;  break;
					case '7': _number = 7;  break;
					case '8': _number = 8;  break;
					case '9': _number = 9;  break;

					}


					_major = _major * 10 + _number;

				}

				else break;

				if (m_ID < m_Size) ++m_ID;

				else m_Valid = false;

				*outData = _major;
			}

		}

		//==============================================================
		//==============================================================

		void CText::getFloat(float *data) {

			char _symbol;

			while (m_Valid) {

				_symbol = m_Data[m_ID];

				if (_symbol > 0x2F && _symbol < 0x3A) break;

				if (m_ID < m_Size) ++m_ID;

				else m_Valid = false;
			}

			uint32_t _major = 0;
			uint32_t _minor = 0.0f;
			uint32_t _minorDigit = 1;
			bool _separator = false;

			while (m_Valid) {

				_symbol = m_Data[m_ID];

				if ((_symbol > 0x2F && _symbol < 0x3A) || _symbol == '.') {

					if (_symbol == '.') _separator = true;

					else {

						uint32_t _number = 0;
						switch (_symbol) {

						case '0': _number = 0;  break;
						case '1': _number = 1;  break;
						case '2': _number = 2;  break;
						case '3': _number = 3;  break;
						case '4': _number = 4;  break;
						case '5': _number = 5;  break;
						case '6': _number = 6;  break;
						case '7': _number = 7;  break;
						case '8': _number = 8;  break;
						case '9': _number = 9;  break;
						}

						if (!_separator) _major = _major * 10 + _number;
						else {

							_minorDigit *= 10;
							_minor = _minor * 10 + _number;


						}

					}


				}

				else break;

				if (m_ID < m_Size) ++m_ID;

				else m_Valid = false;

			}

			*data = (float)_major + ((float)_minor / (float)_minorDigit);

		}

		void CText::getFloat(char *word) {

			uint32_t	_idWord = 0;
			char		_symbol = m_Data[m_ID];

			if (m_ID >= m_Size) m_Valid = false;

			while (m_Valid) {

				if (_symbol > 0x2F && _symbol < 0x3A) {

					break;

				}

				if (m_ID < m_Size) _symbol = m_Data[++m_ID];

				else m_Valid = false;

			}

			while (m_Valid) {

				if ((_symbol > 0x2F && _symbol < 0x3A) || _symbol == '.') {

					word[_idWord++] = _symbol;

				}

				else break;

				if (m_ID < m_Size) _symbol = m_Data[++m_ID];

				else m_Valid = false;

			}

			word[_idWord++] = 0;
		}

		//==============================================================
		//==============================================================v

		size_t CText::getToSupremum(char *word, char supremum) {

			uint32_t	_offset = 0;
			uint32_t	_idWord = 0;

			while (m_Valid) {

				char _symbol = m_Data[m_ID];

				if (_symbol == supremum) break;

				word[_idWord++] = _symbol;

				if (m_ID < m_Size) ++m_ID;

				else m_Valid = false;
			}


			word[_idWord++] = 0;

			return m_ID - _offset;

		}

		//==============================================================
		//==============================================================

		size_t CText::getInfSup(char *word, char infimum, char supremum) {

			uint32_t	_idWord = 0;
			char		_symbol = m_Data[m_ID];

			while (m_Valid) {

				_symbol = m_Data[m_ID];

				if (m_ID < m_Size) ++m_ID;

				else m_Valid = false;

				if (_symbol == infimum) break;
			}

			while (m_Valid) {

				_symbol = m_Data[m_ID];

				if (_symbol == supremum) break;

				word[_idWord++] = _symbol;

				if (m_ID < m_Size) ++m_ID;

				else m_Valid = false;
			}

			word[_idWord++] = 0;

			return _idWord;
		}

		//==============================================================
		//==============================================================

		void CText::getWord(char *word) {

			uint32_t	_idWord = 0;
			char		_symbol = m_Data[m_ID];

			if (m_ID >= m_Size) m_Valid = false;

			while (m_Valid) {

				if (_symbol > 0x40 && _symbol < 0x5B) {

					break;

				}
				else if (_symbol > 0x60 && _symbol < 0x7B) {

					break;

				}

				if (m_ID >= m_Size)  m_Valid = false;

				_symbol = m_Data[++m_ID];

			}

			while (m_Valid) {

				if (_symbol > 0x0 && _symbol < 0x41) {

					break;

				}
				else if (_symbol > 0x5A && _symbol < 0x61) {

					break;

				}

				else if (_symbol > 0x7A) {

					break;

				}

				word[_idWord++] = _symbol;

				if (m_ID >= m_Size) m_Valid = false;

				_symbol = m_Data[++m_ID];

			}

			word[_idWord++] = 0;

		}

	} // namespace CONTENT

} // namespace FE

