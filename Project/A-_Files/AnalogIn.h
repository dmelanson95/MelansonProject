/* AnalogIn.h
 *
 * Header file created by David Melanson
 * for IoT Homework Problem 2
 *
 */
 
class AnalogIn {
	private:
		unsigned int number;

	public:
		AnalogIn();
		AnalogIn(unsigned int n);
		virtual unsigned int getNumber(){return number;}
		virtual void setNumber(unsigned int n);
		virtual int readAdcSample();
		virtual ~AnalogIn();
};
