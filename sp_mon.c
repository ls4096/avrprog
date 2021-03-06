#include "sp_mon.h"

#include "reg_mem.h"

static volatile unsigned short _sp_buckets[SP_MON_NUM_BUCKETS];
static volatile bool _enable = false;


void sp_mon_enable(bool enable)
{
	_enable = enable;
	if (_enable)
	{
		short i;
		for (i = 0; i < SP_MON_NUM_BUCKETS; i++)
		{
			_sp_buckets[i] = 0;
		}
	}
}

void sp_mon_check()
{
	if (!_enable)
	{
		return;
	}

	unsigned short sp = REG_SP;
	_sp_buckets[sp >> SP_MON_BUCKET_SIZE_BITS]++;
}

volatile unsigned short* sp_mon_get_buckets()
{
	return _sp_buckets;
}
