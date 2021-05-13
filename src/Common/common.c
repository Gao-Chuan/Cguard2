#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"
#include "amazonMQTT.h"
#include "HAP.h"
#include "homekit.h"
#include "HAPAccessorySetup.h"


// Homekit setup code init API.
int PrepareNewSetupCode(void);

int PrepareNewSetupCode(void)
{
    HAPSetupCode setupCode;
    HAPAccessorySetupGenerateRandomSetupCode(&setupCode);
    // printf("\n****************HomeKit Setup Code is %s *********************\n", setupCode.stringValue);
    // Setup info.
    HAPSetupInfo setupInfo;
    HAPPlatformRandomNumberFill(setupInfo.salt, sizeof setupInfo.salt);
    const uint8_t srpUserName[] = "Pair-Setup";
    
    // // ***for debug purpose only
    memcpy(setupCode.stringValue, "111-22-333", sizeof(setupCode.stringValue));
    // // ***end debug

    HAP_srp_verifier(
            setupInfo.verifier,
            setupInfo.salt,
            srpUserName,
            sizeof srpUserName - 1,
            (const uint8_t*) setupCode.stringValue,
            sizeof setupCode.stringValue - 1);

    FILE *fp = fopen("./.HomeKitStore/40.10", "wb");
    if (fp == NULL) {
        printf("Create setup file failed.\n");
        return -1;
    } else
    {
        fwrite(&setupInfo, sizeof(HAPSetupInfo), 1, fp);
        fclose(fp);
    }
    
    return 0;
}
