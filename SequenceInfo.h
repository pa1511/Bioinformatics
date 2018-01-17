/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File: SequenceInfo.h
 * Author: paf
 *
 * Created on January 15, 2018, 12:57 PM
 */

#ifndef SEQUENCEINFO_H
#define SEQUENCEINFO_H

#ifdef __cplusplus
extern "C" {
#endif

namespace bioinformatics {
    struct SequenceInfo {
        std::string name;
        int length;
    };
}


#ifdef __cplusplus
}
#endif

#endif /* SEQUENCEINFO_H */

