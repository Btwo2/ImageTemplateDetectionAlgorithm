# Proof Of Delivery System Using Template Matching

![templates](https://github.com/Btwo2/ProofOfDelivery/assets/110456965/9aa527d1-e609-4b30-8d28-1000ba12f832)

Developed a Proof of Delivery method applying template matching method to a photo taken from a filled payment stub. Considering three kinds of stub template it is applyied a sequence of operations to seach through all image extension where is the most probable point to be the center of the template and it's actual size. From that process we get the rotation, size, offset and correlation of the stub in relation to the stub template detected. 

## Cekeikon

A Portuguese extension library created by [Hae Yong Kim](http://www.lps.usp.br/hae/) to make it easier to use some classes and functions in C++. This project uses this library with the purpose of ease imagem manipulation and filtering. This solution uses [Cekeikon](http://www.lps.usp.br/hae/software/cekeikon56.html) to ease image computing and manipulation.  

## Payment Stub Templates

For this project we will consider as standard just 3 kinds of stub template. This templates were adapted from original ones containing only 0, 255 and 128 pixel values, where 128 refers to pixels that should be ignored (don't care).

![template](https://github.com/Btwo2/ProofOfDelivery/assets/110456965/637ab459-1a93-48bd-b112-429b088b9065)

## Results

As result, it was possible to detect all 20 examples proposed. After finding the highest correlation, the correspondant stub template is painted over the original image so that we can assure that is really found what we want and where it really is in the image. 

![result](https://github.com/Btwo2/ProofOfDelivery/assets/110456965/8f8588ed-6e82-4c5e-9895-87e47e3e166d)
