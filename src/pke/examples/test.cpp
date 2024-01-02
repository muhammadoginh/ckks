//==================================================================================
// BSD 2-Clause License
//
// Copyright (c) 2014-2022, NJIT, Duality Technologies Inc. and other contributors
//
// All rights reserved.
//
// Author TPOC: contact@openfhe.org
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==================================================================================

/*

Example for CKKS bootstrapping with sparse packing

*/

#define PROFILE

#include "openfhe.h"
#include <filesystem>
#include <iostream>

using namespace lbcrypto;

void BootstrapExample(uint32_t numSlots, uint32_t case_num, uint32_t curr_level, uint32_t ring_dim);

int main(int argc, char* argv[]) {
    // We run the example with 8 slots and ring dimension 4096 to illustrate how to run bootstrapping with a sparse plaintext.
    // Using a sparse plaintext and specifying the smaller number of slots gives a performance improvement (typically up to 3x).


    // I/O FILE DIRCETORY RESET / GENERATION
    std::filesystem::path p_ofhe_io("./ofhe_io");
    if(std::filesystem::exists(p_ofhe_io)) std::filesystem::remove_all(p_ofhe_io);  // Remove all IO files
    std::filesystem::create_directory(p_ofhe_io);    

    std::filesystem::path p_key_mult("./ofhe_io/key_mult");
    std::filesystem::create_directory(p_key_mult);

    std::filesystem::path p_key_mult_key_switching_key("./ofhe_io/key_mult/key_switching_key");
    std::filesystem::create_directory(p_key_mult_key_switching_key);
    std::filesystem::path p_key_mult_output("./ofhe_io/key_mult/output");
    std::filesystem::create_directory(p_key_mult_output);  

    std::filesystem::path p_mult("./ofhe_io/mult");
    std::filesystem::create_directory(p_mult);
    std::filesystem::path p_mult_input("./ofhe_io/mult/input");
    std::filesystem::create_directory(p_mult_input);

    std::filesystem::path p_ks("./ofhe_io/ks");
    std::filesystem::create_directory(p_ks);
    std::filesystem::path p_ks_input("./ofhe_io/ks/input");
    std::filesystem::create_directory(p_ks_input);
    std::filesystem::path p_ks_output("./ofhe_io/ks/output");
    std::filesystem::create_directory(p_ks_output);

    std::filesystem::path p_mod_up("./ofhe_io/mod_up");
    std::filesystem::create_directory(p_mod_up);
    std::filesystem::path p_mod_up_bconv_in("./ofhe_io/mod_up/bconv_in");
    std::filesystem::create_directory(p_mod_up_bconv_in);
    std::filesystem::path p_mod_up_bconv_out("./ofhe_io/mod_up/bconv_out");
    std::filesystem::create_directory(p_mod_up_bconv_out);
    std::filesystem::path p_mod_up_bconv_param("./ofhe_io/mod_up/bconv_param");
    std::filesystem::create_directory(p_mod_up_bconv_param);
    std::filesystem::path p_mod_up_bconv_param_PartQlHat_inv_modqi("./ofhe_io/mod_up/bconv_param/PartQlHat_inv_modqi");
    std::filesystem::create_directory(p_mod_up_bconv_param_PartQlHat_inv_modqi);
    std::filesystem::path p_mod_up_bconv_param_PartQlHatModpi("./ofhe_io/mod_up/bconv_param/PartQlHatModpi");
    std::filesystem::create_directory(p_mod_up_bconv_param_PartQlHatModpi);
    std::filesystem::path p_mod_up_modup_in("./ofhe_io/mod_up/input");
    std::filesystem::create_directory(p_mod_up_modup_in);
    std::filesystem::path p_mod_up_modup_out("./ofhe_io/mod_up/output");
    std::filesystem::create_directory(p_mod_up_modup_out);

    std::filesystem::path p_mod_down("./ofhe_io/mod_down");
    std::filesystem::create_directory(p_mod_down);
    std::filesystem::path p_mod_down_output("./ofhe_io/mod_down/output");
    std::filesystem::create_directory(p_mod_down_output);
    std::filesystem::path p_mod_down_bconv_in("./ofhe_io/mod_down/bconv_in");
    std::filesystem::create_directory(p_mod_down_bconv_in);
    std::filesystem::path p_mod_down_bconv_out("./ofhe_io/mod_down/bconv_out");
    std::filesystem::create_directory(p_mod_down_bconv_out);
    std::filesystem::path p_mod_down_subtraction("./ofhe_io/mod_down/subtraction");
    std::filesystem::create_directory(p_mod_down_subtraction);
    std::filesystem::path p_mod_down_subtraction_in("./ofhe_io/mod_down/subtraction/input");
    std::filesystem::create_directory(p_mod_down_subtraction_in);
    std::filesystem::path p_mod_down_subtraction_out("./ofhe_io/mod_down/subtraction/output");
    std::filesystem::create_directory(p_mod_down_subtraction_out);
    std::filesystem::path p_mod_down_subtraction_param("./ofhe_io/mod_down/subtraction/param");
    std::filesystem::create_directory(p_mod_down_subtraction_param);
    std::filesystem::path p_mod_down_bconv_param("./ofhe_io/mod_down/bconv_param");
    std::filesystem::create_directory(p_mod_down_bconv_param);
    std::filesystem::path p_mod_down_bconv_param_PHatInvModpi("./ofhe_io/mod_down/bconv_param/PHatInvModpi");
    std::filesystem::create_directory(p_mod_down_bconv_param_PHatInvModpi);
    std::filesystem::path p_mod_down_bconv_param_PHatModqi("./ofhe_io/mod_down/bconv_param/PHatModqi");
    std::filesystem::create_directory(p_mod_down_bconv_param_PHatModqi);
    

    std::filesystem::path p_rns_decompose("./ofhe_io/rns_decompose");
    std::filesystem::create_directory(p_rns_decompose);

    // Key-Switching SCENARIO CONFIGURATION
    int case_num = 3;
    int curr_level_plus_one = 2; // =l+1 (<=L+1) (if l=0 occurs error)
    int ring_dim = 1<<2;
    BootstrapExample(2, case_num, curr_level_plus_one, ring_dim);
}

void BootstrapExample(uint32_t numSlots, uint32_t case_num, uint32_t curr_level_plus_one, uint32_t ring_dim) {
    // Chulwoo: Turn-Off COUT
    // std::cout.setstate(std::ios_base::failbit);

    int case_dnum, case_levelsUsedBeforeBootstrap, case_initial_level;

    case_initial_level = curr_level_plus_one - 1;

    switch(case_num){
        case 1:
            case_dnum = 1;
            case_levelsUsedBeforeBootstrap = 1; // L+1 = 15
        break;
        case 2:
            case_dnum = 2;
            case_levelsUsedBeforeBootstrap = 6; // L+1 = 20
        break;
        case 3:
            case_dnum = 4;
            case_levelsUsedBeforeBootstrap = 10; // L+1 = 24
        break;
        case 4:
            case_dnum = 9;
            case_levelsUsedBeforeBootstrap = 13; // L+1 = 27
        break;
        default:
            case_dnum = 29;
            case_levelsUsedBeforeBootstrap = 15; // L+1 = 29
        break;
    }

    // Step 1: Set CryptoContext
    CCParams<CryptoContextCKKSRNS> parameters;

    // A. Specify main parameters
    /*  A1) Secret key distribution
    * The secret key distribution for CKKS should either be SPARSE_TERNARY or UNIFORM_TERNARY.
    * The SPARSE_TERNARY distribution was used in the original CKKS paper,
    * but in this example, we use UNIFORM_TERNARY because this is included in the homomorphic
    * encryption standard.
    */
    SecretKeyDist secretKeyDist = UNIFORM_TERNARY;
    parameters.SetSecretKeyDist(secretKeyDist);

    /*  A2) Desired security level based on FHE standards.
    * In this example, we use the "NotSet" option, so the example can run more quickly with
    * a smaller ring dimension. Note that this should be used only in
    * non-production environments, or by experts who understand the security
    * implications of their choices. In production-like environments, we recommend using
    * HEStd_128_classic, HEStd_192_classic, or HEStd_256_classic for 128-bit, 192-bit,
    * or 256-bit security, respectively. If you choose one of these as your security level,
    * you do not need to set the ring dimension.
    */
    parameters.SetSecurityLevel(HEStd_NotSet);
    parameters.SetRingDim(ring_dim);

    /*  A3) Key switching parameters.
    * By default, we use HYBRID key switching with a digit size of 3. => wrong... dnum = 3
    * Choosing a larger digit size can reduce complexity, but the size of keys will increase.
    * Note that you can leave these lines of code out completely, since these are the default values.
    */
    parameters.SetNumLargeDigits(case_dnum); // dnum
    parameters.SetKeySwitchTechnique(HYBRID);

    /*  A4) Scaling parameters.
    * By default, we set the modulus sizes and rescaling technique to the following values
    * to obtain a good precision and performance tradeoff. We recommend keeping the parameters
    * below unless you are an FHE expert.
    */
#if NATIVEINT == 128 && !defined(__EMSCRIPTEN__)
    // Currently, only FIXEDMANUAL and FIXEDAUTO modes are supported for 128-bit CKKS bootstrapping.
    ScalingTechnique rescaleTech = FIXEDAUTO;
    usint dcrtBits               = 64; //78
    usint firstMod               = 65; //89
#else
    // All modes are supported for 64-bit CKKS bootstrapping.
    // ScalingTechnique rescaleTech = FLEXIBLEAUTO;
    ScalingTechnique rescaleTech = FIXEDMANUAL;
    usint dcrtBits               = 47;   //47 => NOT fixed as 47... this could be 48 sometimes.
    usint firstMod               = 48;   //48 => always fixed as 48
    /*
        *** IMPORTANT *** -> Pi bit-size is determined by AUXMODSIZE
        To Change AUXMODSIZE => ckksrns-parametergeneration.cpp
        Default was 60 => changed to 48
    */
#endif

    parameters.SetScalingModSize(dcrtBits);
    parameters.SetScalingTechnique(rescaleTech);
    parameters.SetFirstModSize(firstMod);

    /*  A4) Bootstrapping parameters.
    * We set a budget for the number of levels we can consume in bootstrapping for encoding and decoding, respectively.
    * Using larger numbers of levels reduces the complexity and number of rotation keys,
    * but increases the depth required for bootstrapping.
	* We must choose values smaller than ceil(log2(slots)). A level budget of {4, 4} is good for higher ring
    * dimensions (65536 and higher).
    */
    // std::vector<uint32_t> levelBudget = {3, 3};
    std::vector<uint32_t> levelBudget = {1, 1};

    // We approximate the number of levels bootstrapping will consume to help set our initial multiplicative depth.
    uint32_t approxBootstrapDepth = 6;

    /* We give the user the option of configuring values for an optimization algorithm in bootstrapping.
    * Here, we specify the giant step for the baby-step-giant-step algorithm in linear transforms
    * for encoding and decoding, respectively. Either choose this to be a power of 2
    * or an exact divisor of the number of slots. Setting it to have the default value of {0, 0} allows OpenFHE to choose
    * the values automatically.
    */
    std::vector<uint32_t> bsgsDim = {0, 0};

    /*  A5) Multiplicative depth.
    * The goal of bootstrapping is to increase the number of available levels we have, or in other words,
    * to dynamically increase the multiplicative depth. However, the bootstrapping procedure itself
    * needs to consume a few levels to run. We compute the number of bootstrapping levels required
    * using GetBootstrapDepth, and add it to levelsUsedBeforeBootstrap to set our initial multiplicative
    * depth.
    */
    uint32_t levelsUsedBeforeBootstrap = case_levelsUsedBeforeBootstrap; 
    auto bootstrap_depth = FHECKKSRNS::GetBootstrapDepth(approxBootstrapDepth, levelBudget, secretKeyDist);
    usint depth =
        levelsUsedBeforeBootstrap + bootstrap_depth;
    parameters.SetMultiplicativeDepth(depth);

    // Generate crypto context.
    CryptoContext<DCRTPoly> cryptoContext = GenCryptoContext(parameters);

    // std::cout.setstate(std::ios_base::failbit); // DISABLE COUT

    // PRINTING PARAMETERs
    std::cout << "============ SCHEME ============" << std::endl; 
    std::cout << parameters << std::endl;
    std::cout << "============ SCHEME ============" << std::endl << std::endl;

    // Enable features that you wish to use. Note, we must enable FHE to use bootstrapping.
    cryptoContext->Enable(PKE);
    cryptoContext->Enable(KEYSWITCH);
    cryptoContext->Enable(LEVELEDSHE);
    cryptoContext->Enable(ADVANCEDSHE);
    cryptoContext->Enable(FHE);

    // Step 2: Precomputations for bootstrapping
    cryptoContext->EvalBootstrapSetup(levelBudget, bsgsDim, numSlots);

    // Step 3: Key Generation
    auto keyPair = cryptoContext->KeyGen();
    cryptoContext->EvalMultKeyGen(keyPair.secretKey);

    // Generate bootstrapping keys.
    cryptoContext->EvalBootstrapKeyGen(keyPair.secretKey, numSlots);

    // Step 4: Encoding and encryption of inputs
    // Generate random input
    std::vector<double> x;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (size_t i = 0; i < numSlots; i++) {
        // x.push_back(dis(gen));
        x.push_back(i);
    }

    std::cout << "x: " << x << std::endl;

    // Encoding as plaintexts
    // We specify the number of slots as numSlots to achieve a performance improvement.
    // We use the other default values of depth 1, levels 0, and no params.
    // Alternatively, you can also set batch size as a parameter in the CryptoContext as follows:
    // parameters.SetBatchSize(numSlots);
    // Here, we assume all ciphertexts in the cryptoContext will have numSlots slots.
    // We start with a depleted ciphertext that has used up all of its levels.
    
    uint8_t initial_level = case_initial_level;  // currlent level
    Plaintext ptxt = cryptoContext->MakeCKKSPackedPlaintext(x, 1, depth - initial_level, nullptr, numSlots);
    ptxt->SetLength(numSlots);

    // PRINTING Plaintext Parameters
    std::cout << "============ PlainText Parameters ============" << std::endl;
    std::cout << "Input : " << x;
    std::cout << "Input: " << ptxt;
    usint ringDim = cryptoContext->GetRingDimension();
    std::cout << "Ring Dimension: " << ringDim << std::endl;
    std::cout << "Current LEVEL: " << depth - ptxt->GetLevel() << std::endl;
    std::cout << "Scaling Factor: " << ptxt->GetScalingFactor() << std::endl;
    std::cout << "Modulo of Current Level (q0 * q1 * q2 * ... * qL): " << ptxt->GetElementModulus() << std::endl;
    std::cout << "============ PlainText Parameters ============" << std::endl << std::endl;

    // Encrypt the encoded vectors
    Ciphertext<DCRTPoly> ciph = cryptoContext->Encrypt(keyPair.publicKey, ptxt);
    // Encrypt the encoded vectors
    Ciphertext<DCRTPoly> ciph1 = cryptoContext->Encrypt(keyPair.publicKey, ptxt);

    // PRINT OUT KEY SWITCHING KEY

    auto const ksk = cryptoContext->GetEvalMultKeyVector(ciph->GetKeyTag());

    // PRINTING Ciphertext Parameters
    std::cout << "============ CipherText Parameters ============" << std::endl;
#ifdef PRINT
    std::cout << "Cipher0 ELEMENT(C0): " << ciph->GetElements()[0] << std::endl;
    std::cout << "Cipher0 ELEMENT(C1): " << ciph->GetElements()[1] << std::endl;
    std::cout << "Cipher1 ELEMENT(C0): " << ciph1->GetElements()[0] << std::endl;
    std::cout << "Cipher1 ELEMENT(C1): " << ciph1->GetElements()[1] << std::endl;
#endif
    std::cout << "Scaling Factor: " << ciph->GetScalingFactor() << std::endl;
    std::cout << "Number of Slots: " << ciph->GetSlots() << std::endl;
    std::cout << "Encoding Type: " << ciph->GetEncodingType() << std::endl;
    std::cout << "Cyclotomic Order: " << ciph->GetCryptoParameters()->GetElementParams()->GetCyclotomicOrder() << std::endl;
    std::cout << "Total Modulus Q for maximum level: " << ciph->GetCryptoParameters()->GetElementParams()->GetModulus() << std::endl;
    std::cout << "N: " << ciph->GetCryptoContext()->GetRingDimension() << std::endl;
    std::cout << "Multiplicative Depth: " << depth << std::endl;
    std::cout << "Bootstrapping Depth: " << bootstrap_depth << std::endl;
    std::cout << "L+1: " << ciph->GetCryptoParameters()->GetElementParams()->GetParams().size() << std::endl;
    std::cout << "dnum: " << parameters.GetNumLargeDigits() << std::endl;

    const auto dnum = parameters.GetNumLargeDigits();
    const auto cryptoParams = std::dynamic_pointer_cast<CryptoParametersRNS>(ciph->GetCryptoParameters());
    // const std::shared_ptr<ParmType> paramsP   = cryptoParams->GetParamsP();
    const std::shared_ptr<DCRTPoly::Params> paramsP   = cryptoParams->GetParamsP();
    size_t sizeP   = paramsP->GetParams().size();
    size_t sizeQP   = cryptoParams->GetParamsQP()->GetParams().size();

    std::cout << "k, alpha: " << sizeP << std::endl; // logQ / 60(AUXMODSIZE)
    std::cout << "L+1 + k: " << sizeQP << std::endl;
    std::cout << "============ CipherText Parameters ============" << std::endl << std::endl;

    std::cout << "============ Key Switching KEY ============\n";

    // std::cout << ksk[0]->GetAVector() << std::endl << std::endl;
    // std::cout << ksk[0]->GetBVector() << std::endl << std::endl;
    std::cout << "KSK Dimension 0: " << ksk[0]->GetAVector().size() << " should be same as dnum: " << dnum << std::endl;
    std::cout << "KSK Dimension 1: " << ksk[0]->GetAVector()[0].GetAllElements().size() << " should be same as (L+1 +k): " << sizeQP << std::endl;
    std::cout << "KSK Dimension 2: " << ksk[0]->GetAVector()[0].GetAllElements()[0].GetLength() << " should be same as Ring Dimension: " << ringDim << std::endl;
    std::cout << "KSK Size is dnum * (L+1 +k) * N * 2 = " << dnum * sizeQP * ringDim * 2 << std::endl;

    for (usint i=0; i< dnum; i++) {
        std::ofstream ksk_poly_a("./ofhe_io/key_mult/key_switching_key/ksk_dnum_" + std::to_string(i) + "_A.mem");
        std::ofstream ksk_poly_b("./ofhe_io/key_mult/key_switching_key/ksk_dnum_" + std::to_string(i) + "_B.mem");
        for (usint j=0; j < sizeQP; j++){
            for (usint k=0; k< ringDim; k++){
                ksk_poly_a << ksk[0]->GetAVector()[i].GetAllElements()[j][k] << ' ';
                ksk_poly_b << ksk[0]->GetBVector()[i].GetAllElements()[j][k] << ' ';
            }
            ksk_poly_a << std::endl;
            ksk_poly_b << std::endl;
        }

        ksk_poly_a.close();
        ksk_poly_b.close();
    }
    

    std::cout << "============ Key Switching KEY ============\n";

    // std::ofstream ksk_a_file("io_files/ksk_a.txt");
    // std::ofstream ksk_b_file("io_files/ksk_b.txt");
    // for(usint k=0; k<dnum; k++){
    //     for(usint i=0;i<sizeQP;i++){
    //         for(usint j=0;j<ringDim;j++){
    //             ksk_a_file << ksk[0]->GetAVector()[k].GetAllElements()[i][j] << ' ';
    //             ksk_b_file << ksk[0]->GetBVector()[k].GetAllElements()[i][j] << ' ';
    //         }
    //         ksk_a_file << std::endl;
    //         ksk_b_file << std::endl;
    //     }
    // }

    // ksk_a_file.close();
    // ksk_b_file.close();

    // ciph->GetLevel()
    // pke/include/ciphertext.h
    // Get the number of scalings performed
    std::cout << std::endl << "Number of levels remaining of ciph before MULTIPLICATION: " << depth - ciph->GetLevel() << std::endl;

    // Step 5: Perform the bootstrapping operation. The goal is to increase the number of levels remaining
    // for HE computation.
    std::cout << "============ MULTIPLICATION START ============" << std::endl;
    auto ciphertextAfter = cryptoContext->EvalMult(ciph, ciph1);
    std::cout << "============ MULTIPLICATION END ============" << std::endl;

    std::cout << "Number of levels remaining after multiplication: " << depth - ciphertextAfter->GetLevel() << std::endl
              << std::endl;


    // std::cout.clear(); // ENABLE COUT

    // Step 7: Decryption and output
    Plaintext result;
    cryptoContext->Decrypt(keyPair.secretKey, ciphertextAfter, &result);
    result->SetLength(numSlots);
    std::cout << "Output of Sqaure is \n\t" << result << std::endl;
}

/*
1. EvalMult
pke/schemebase/base-scheme.h
    pke/lib/schemebase/base-leveledshe.cpp

2. ptxt->GetEncodingParams()
pke/include/encoding/encodingparams.h

p = plaintext modulus that is used by all schemes
rootP = root of unity for plaintext modulus
bigP = big plaintext modulus that is used for arbitrary cyclotomics
rootBigP = root of unity for big plaintext modulus
g = plaintext generator is used for packed encoding (to find the correct automorphism index)
L = maximum batch size used by EvalSumKeyGen for packed encoding

3. HYBRID KeySwitching
number of towers withing every digit = alpha = (L+1)/dnum

*/
