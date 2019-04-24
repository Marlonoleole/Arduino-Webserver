#ifndef STRING_H
#define STRING_H
namespace Standard
{
	//free functions for the benefit of the class and the user
	unsigned long string_length(const char *chars);
	void string_copy(char *dest, const char *source, const int length);
	int string_compare(const char *first, const char *second);
	int string_find_first_of(const char *chars, const int length, const char symbol);
	int string_find_first_of(const char *chars, const int length, const char *symbols);
	bool string_verify(const char *chars, const int length);


	class string
	{
		private:
		unsigned long length_{0};
		char *chars_;

		public:
		string()
		{
			length_ = 0;
			chars_ = new char[length_ + 1];
			chars_[0] = '\0';
		}
		string(const char *text)
		{
			length_ = string_length(text);
			chars_ = new char[length_ + 1];
			string_copy(chars_, text, length_);
		}
		string(const string &other)
		{
			length_ = other.length_;
			chars_ = new char[other.length_ + 1];
			string_copy(chars_, other.chars_, other.length_);
		}
		~string()
		{
			delete[] chars_;
		}
		int size() const { return length_; }
		char &operator[](const int index) const { return chars_[index]; }
		operator char *() const { return chars_; }
		bool operator==(const string &other) const { return string_compare(chars_, other.chars_) == 0; }
		bool operator<(const string &other) const { return string_compare(chars_, other.chars_) < 0; }
		bool operator>(const string &other) const { return string_compare(chars_, other.chars_) > 0; }
		bool operator!=(const string &other) const { return string_compare(chars_, other.chars_) != 0; };
		void operator+=(const string &other)
		{
			unsigned long new_length = other.length_ + length_;
			char *old = chars_;
			chars_ = new char[new_length + 1];
			unsigned long i = 0;
			while (i < length_)
			{
				chars_[i] = old[i];
				++i;
			}
			while (i < new_length)
			{
				chars_[i] = other[i - length_];
				++i;
			}
			chars_[new_length] = '\0';
			length_ = new_length;
			delete[] old;
		}
		void operator+=(const char add)
		{
			char *old = chars_;
			unsigned long new_length = length_+1;
			chars_ = new char[length_+2];
			unsigned long i = 0;
			while (i< length_)
			{
				chars_[i] = old[i];
			}
			chars_[length_] = add;
			chars_[new_length] = '\0';
			length_ = new_length;
			delete[] old;
		}
		string operator=(const string &other)
		{
			delete[] chars_;
			chars_ = new char[other.length_];
			length_ = other.length_;
			string_copy(chars_, other.chars_, length_);
			return *this;
		}
		int find_first_of(const char ch)
		{
			return string_find_first_of(chars_, length_, ch);
		}
		int find_first_of(const string &other)
		{
			return string_find_first_of(chars_, length_, other.chars_);
		}
		char *c_str() const
		{
			return chars_;
		}
		string substr(const int first, const int ReadLength)
		{
			int length = ReadLength;
			char *new_str = new char[length + 1];
			for (int index = 0; index < length; ++index)
			{
				new_str[index] = chars_[index + first];
			}
			new_str[length] = '\0';
			string rs = string(new_str);
			delete[] new_str;
			return rs;
		}
		string reverse()
		{
			string new_str = string(chars_);
			unsigned long first =0;
			unsigned long last = length_ -1;
			while (first != last && first <last)
			{
				char hold = new_str.chars_[last];
				new_str[last] = new_str[first];
				new_str[first] = hold;
				++first;
				--last;
			}
			return new_str;
		}
	};
	int hash_code(const string &i);
	template <typename T>
	string parse_single(T numb)
	{
		switch(numb)
		{
			case 0: return "0";
			case 1: return "1";
			case 2: return "2";
			case 3: return "3";
			case 4: return "4";
			case 5:	return "5";
			case 6:	return "6";
			case 7: return "7";
			case 8: return "8";
			case 9: return "9";
			default: return "0";
		}
	}
	
	template <typename T>
	string parse_int(T value)
	{
		T number = value;
		string res ="";
		string prefix = "";
		if(number < 0)
		{
			prefix = "-";
			number = number * -1;
			
		}
		if(number < 10)
		{
			res += parse_single(number);
		} else
		{
			int buffer = number;
			while (buffer > 0)
			{
				res+=parse_single(buffer%10);
				buffer/=10;
			}
		}
		res = res.reverse();
		string return_obj = prefix;
		return_obj += res;
		return return_obj;
	}
} // namespace Standard
#endif