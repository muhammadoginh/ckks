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
  Simple examples for CKKS
 */

#define PROFILE

#include "openfhe.h"
#include <filesystem>

using namespace lbcrypto;

int main() {


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


    // Step 1: Setup CryptoContext

    // A. Specify main parameters
    /* A1) Multiplicative depth:
   * The CKKS scheme we setup here will work for any computation
   * that has a multiplicative depth equal to 'multDepth'.
   * This is the maximum possible depth of a given multiplication,
   * but not the total number of multiplications supported by the
   * scheme.
   *
   * For example, computation f(x, y) = x^2 + x*y + y^2 + x + y has
   * a multiplicative depth of 1, but requires a total of 3 multiplications.
   * On the other hand, computation g(x_i) = x1*x2*x3*x4 can be implemented
   * either as a computation of multiplicative depth 3 as
   * g(x_i) = ((x1*x2)*x3)*x4, or as a computation of multiplicative depth 2
   * as g(x_i) = (x1*x2)*(x3*x4).
   *
   * For performance reasons, it's generally preferable to perform operations
   * in the shorted multiplicative depth possible.
   */
    uint32_t multDepth = 2; // this is the same as level

    /* A2) Bit-length of scaling factor.
   * CKKS works for real numbers, but these numbers are encoded as integers.
   * For instance, real number m=0.01 is encoded as m'=round(m*D), where D is
   * a scheme parameter called scaling factor. Suppose D=1000, then m' is 10 (an
   * integer). Say the result of a computation based on m' is 130, then at
   * decryption, the scaling factor is removed so the user is presented with
   * the real number result of 0.13.
   *
   * Parameter 'scaleModSize' determines the bit-length of the scaling
   * factor D, but not the scaling factor itself. The latter is implementation
   * specific, and it may also vary between ciphertexts in certain versions of
   * CKKS (e.g., in FLEXIBLEAUTO).
   *
   * Choosing 'scaleModSize' depends on the desired accuracy of the
   * computation, as well as the remaining parameters like multDepth or security
   * standard. This is because the remaining parameters determine how much noise
   * will be incurred during the computation (remember CKKS is an approximate
   * scheme that incurs small amounts of noise with every operation). The
   * scaling factor should be large enough to both accommodate this noise and
   * support results that match the desired accuracy.
   */
    uint32_t scaleModSize = 20;

    /* A3) Number of plaintext slots used in the ciphertext.
   * CKKS packs multiple plaintext values in each ciphertext.
   * The maximum number of slots depends on a security parameter called ring
   * dimension. In this instance, we don't specify the ring dimension directly,
   * but let the library choose it for us, based on the security level we
   * choose, the multiplicative depth we want to support, and the scaling factor
   * size.
   *
   * Please use method GetRingDimension() to find out the exact ring dimension
   * being used for these parameters. Give ring dimension N, the maximum batch
   * size is N/2, because of the way CKKS works.
   */
    uint32_t batchSize = 1; // originally 8

    /* A4) Desired security level based on FHE standards.
   * This parameter can take four values. Three of the possible values
   * correspond to 128-bit, 192-bit, and 256-bit security, and the fourth value
   * corresponds to "NotSet", which means that the user is responsible for
   * choosing security parameters. Naturally, "NotSet" should be used only in
   * non-production environments, or by experts who understand the security
   * implications of their choices.
   *
   * If a given security level is selected, the library will consult the current
   * security parameter tables defined by the FHE standards consortium
   * (https://homomorphicencryption.org/introduction/) to automatically
   * select the security parameters. Please see "TABLES of RECOMMENDED
   * PARAMETERS" in  the following reference for more details:
   * http://homomorphicencryption.org/wp-content/uploads/2018/11/HomomorphicEncryptionStandardv1.1.pdf
   */
    CCParams<CryptoContextCKKSRNS> parameters;
    parameters.SetMultiplicativeDepth(multDepth);
    parameters.SetScalingModSize(scaleModSize);
    parameters.SetBatchSize(batchSize);
    // parameters.SetRingDim(4);

    CryptoContext<DCRTPoly> cc = GenCryptoContext(parameters);
    // this code use src\pke\lib\schemerns\rns-cryptoparameters.cpp

    // Enable the features that you wish to use
    cc->Enable(PKE);  // this is for KeyGen operation
    cc->Enable(KEYSWITCH); // this line to enable keyswitching, by default OpenFHE use HYBRID key switching 
    cc->Enable(LEVELEDSHE); // this is for EvalMultKeyGen operation

    // B. Step 2: Key Generation
    /* B1) Generate encryption keys.
   * These are used for encryption/decryption, as well as in generating
   * different kinds of keys.
   */
    auto keys = cc->KeyGen();

    /* B2) Generate the digit size
   * In CKKS, whenever someone multiplies two ciphertexts encrypted with key s,
   * we get a result with some components that are valid under key s, and
   * with an additional component that's valid under key s^2.
   *
   * In most cases, we want to perform relinearization of the multiplicaiton
   * result, i.e., we want to transform the s^2 component of the ciphertext so
   * it becomes valid under original key s. To do so, we need to create what we
   * call a relinearization key with the following line.
   */
    cc->EvalMultKeyGen(keys.secretKey);

    /* B3) Generate the rotation keys
   * CKKS supports rotating the contents of a packed ciphertext, but to do so,
   * we need to create what we call a rotation key. This is done with the
   * following call, which takes as input a vector with indices that correspond
   * to the rotation offset we want to support. Negative indices correspond to
   * right shift and positive to left shift. Look at the output of this demo for
   * an illustration of this.
   *
   * Keep in mind that rotations work over the batch size or entire ring dimension (if the batch size is not specified).
   * This means that, if ring dimension is 8 and batch
   * size is not specified, then an input (1,2,3,4,0,0,0,0) rotated by 2 will become
   * (3,4,0,0,0,0,1,2) and not (3,4,1,2,0,0,0,0).
   * If ring dimension is 8 and batch
   * size is set to 4, then the rotation of (1,2,3,4) by 2 will become (3,4,1,2).
   * Also, as someone can observe
   * in the output of this demo, since CKKS is approximate, zeros are not exact
   * - they're just very small numbers.
   */
    // cc->EvalRotateKeyGen(keys.secretKey, {1, -2});

    // Step 3: Encoding and encryption of inputs

    // Inputs
    std::vector<double> m1 = {0.4};
    std::vector<double> m2 = {0.5};

    // Encoding as plaintexts
    Plaintext ptxt1 = cc->MakeCKKSPackedPlaintext(m1);
    Plaintext ptxt2 = cc->MakeCKKSPackedPlaintext(m2);

    // PRINTING Plaintext Parameters
    std::cout << "Input m1: " << m1 << std::endl;
    std::cout << "Input m2: " << m2 << std::endl;

    std::cout << "============ PlainText Parameters ============" << std::endl;
    std::cout << "CKKS scheme is using ring dimension " << cc->GetRingDimension() << std::endl;
    std::cout << "Current MultDepth: " << multDepth - ptxt1->GetLevel() << std::endl;
    std::cout << "Scaling Factor: " << ptxt1->GetScalingFactor() << std::endl;
    std::cout << "============ PlainText Parameters ============" << std::endl << std::endl;

    // std::cout << "Plaintext m1: " << ptxt1->GetElements() << std::endl;
    // std::cout << "Plaintext m2: " << ptxt2->GetElement() << std::endl;

    // Client Encrypt a the encoded vectors
    auto c1 = cc->Encrypt(keys.publicKey, ptxt1);
    auto c2 = cc->Encrypt(keys.publicKey, ptxt2);

    // PRINTING Ciphertext Parameters
    std::cout << "============ CipherText Parameters ============" << std::endl;

    // PRINT OUT KEY SWITCHING KEY

    auto const ksw = cc->GetEvalMultKeyVector(c1->GetKeyTag());

    // Step 4: Evaluation


    // Homomorphic multiplication
    auto cMul = cc->EvalMult(c1, c2);
    // std::cout << "cMul :" << cMul << std::endl; 
    // std::ofstream cMul_file ("content_of_cMul_without_keySwitching.txt");
    // cMul_file << "cMul: \n" << cMul << std::endl; 
    // cMul_file.close();

    // Step 5: Decryption and output
    Plaintext result;
    // We set the cout precision to 4 decimal digits for a nicer output.
    // If you want to see the error/noise introduced by CKKS, bump it up
    // to 15 and it should become visible.
    std::cout.precision(4);

    std::cout << std::endl << "Results of homomorphic computations: " << std::endl;

    cc->Decrypt(keys.secretKey, c1, &result);
    result->SetLength(batchSize);
    std::cout << "m1 = " << result;

    cc->Decrypt(keys.secretKey, c2, &result);
    result->SetLength(batchSize);
    std::cout << "m2 = " << result;

    // Decrypt the result of multiplication
    cc->Decrypt(keys.secretKey, cMul, &result);
    result->SetLength(batchSize);
    std::cout << "m1 * m2 = " << result << std::endl;

    return 0;
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


*/

