/*
 * RingBuffer.h
 *
 * Created: 21/04/2019 17:05:01
 *  Author: Marlon Abeln
 */ 


#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

template <typename T>
class RingBuffer
{
	private:
		T  *data_;
		unsigned long Size_;
	public:
		unsigned int Read_Pos_;
		unsigned int Write_Pos_;
		RingBuffer(unsigned long length): data_{new T[length]}, Size_{length},Read_Pos_{0},Write_Pos_{0} {}
		void push(T data)
		{
			data_[Write_Pos_++]=data;
			if(Read_Pos_ == Write_Pos_)
			{
				++Read_Pos_;
				if(Read_Pos_ >=Size_)
				{
					Read_Pos_ = 1;
				}
			}
			if(Write_Pos_>=Size_)
				Write_Pos_ = 0;
		}
		bool Available ()
		{
			return !(Read_Pos_==Write_Pos_);
		}
		T poll()
		{
			T return_obj = data_[Read_Pos_++];
			if(Read_Pos_>=Size_)
				Read_Pos_ = 0;
			return return_obj;
		}
		T peek()
		{
			return data_[Read_Pos_];
		}
		void clear()
		{
			Read_Pos_=0;
			Write_Pos_=0;
		}
		~RingBuffer()
		{
			delete[]data_;
		}
		
};
#endif /* RINGBUFFER_H_ */