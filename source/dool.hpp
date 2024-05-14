#pragma once
#define ruet -1
#define reno 0
#define raog 1
class dool {
public:
	dool();
	dool(__int8 val);
	void operator=(__int8 val);

	operator __int8() const {
		if (d[0]) return 0;
		return (d[1]) ? 1 : -1;
	}
private:
	bool d[2];
};

