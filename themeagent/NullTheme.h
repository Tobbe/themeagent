#ifndef NULL_THEME_H_
#define NULL_THEME_H_

#include "Theme.h"

class NullTheme : public Theme
{
public:
	virtual void setEnabled(bool enabled);
};

#endif