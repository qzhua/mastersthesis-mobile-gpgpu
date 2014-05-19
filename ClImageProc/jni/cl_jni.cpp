#include "cl_jni.h"

#include <assert.h>
#include <string.h>

#include "cl_base.h"
#include "cl_imgconv.h"
#include "cl_hough.h"

static int progType = -1;
static CLBase *clCtrl = NULL;
		LOGERR("CL controller object already initialized!");
		return 1;
	}

	progType = type;

	if (progType == PROG_TYPE_IMGCONV) {
		LOGINFO("Creating CL program for type %d (PROG_TYPE_IMGCONV)", progType);

		clCtrl = new CLImgConv();
	} else if (progType == PROG_TYPE_HOUGH) {
		LOGINFO("Creating CL program for type %d (PROG_TYPE_HOUGH)", progType);

		clCtrl = new CLHough();
	} else {
		LOGERR("CL program type %d not supported!", progType);
		return 1;
	}

	if (!clCtrl->isInitialized()) {
		LOGERR("Error initializing CL controller object");

		delete clCtrl;
		clCtrl = NULL;

		return 1;
	}

	return 0;
}
													   jobject progSrcBuf)
	assert(clCtrl != NULL);

	// get the name
	char *clKernelProgName = (char *)(env->GetStringUTFChars(progName, NULL));

	LOGINFO("Full source:\n%s", progSrcFull);
	// CL requires to have source code parts of max. 1024 bytes length, so we need
	// to create these parts and devide "progSrcFull":
	const int SRC_MAX_BYTES = 1024;
	const unsigned int numSrcParts = progSizeFull / SRC_MAX_BYTES + 1;
	char **srcParts = new char*[numSrcParts];
	size_t *srcPartsLen = new size_t[numSrcParts];
	LOGINFO("Source parts = %d", numSrcParts);
	for (int i = 0; i < numSrcParts; i++) {
		// create memory space
		const size_t partLen = (i < numSrcParts - 1) ? SRC_MAX_BYTES : progSizeFull - i * SRC_MAX_BYTES;
		srcParts[i] 	= new char[partLen];
		srcPartsLen[i] 	= partLen;

		LOGINFO("Source part %d with str. length %d", i, partLen);

		// copy substring
		strncpy(srcParts[i], progSrcFull + i * SRC_MAX_BYTES, partLen);
	}
	// now create the program
	if (!clCtrl->createProg(clKernelProgName, (const char **)srcParts, numSrcParts, srcPartsLen)) {
		return 1;
	}

	// now create the sampler
	if (!clCtrl->createSampler()) {
		return 1;
	}

	return 0;

	if (clCtrl->createKernel()) {
		return 0;
	} else {
		return 1;
	}

	if (clCtrl->createQueue()) {
		return 0;
	} else {
		return 1;
	}
	assert(clCtrl != NULL);

    	return -1.0f;
    }
    float execTime = displayExecTime("input memory copy");
	assert(clCtrl != NULL);

    	return -1.0f;
    }
	assert(clCtrl != NULL);

		return -1.0f;
	}
		delete clCtrl;
		clCtrl = NULL;
	}