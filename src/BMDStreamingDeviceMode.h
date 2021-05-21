#ifndef BMDStreamingDeviceMode_h
#define BMDStreamingDeviceMode_h

#include "const_str.h"
#include "../DeckLinkAPI_h.h"

#define _CRT_SECURE_NO_WARNINGS

static const void* BMDStreamingDeviceMode_pairs[] =
{
    (void*)bmdStreamingDeviceIdle, "The streaming device is idle.",
    (void*)bmdStreamingDeviceEncoding, "The streaming device is encoding.",
    (void*)bmdStreamingDeviceStopping, "The streaming device is stopping.",
    (void*)bmdStreamingDeviceUnknown, "The streaming device is in an unknown state.",
    NULL, NULL
};

#pragma warning(push)
#pragma warning(disable: 4311)
#pragma warning(disable: 4302)
CONST_FROM_CHAR(BMDStreamingDeviceMode, BMDStreamingDeviceMode_pairs);
CONST_TO_CHAR(BMDStreamingDeviceMode, BMDStreamingDeviceMode_pairs);
#pragma warning(pop)

#endif
