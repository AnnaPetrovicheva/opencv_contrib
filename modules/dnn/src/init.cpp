/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2013, OpenCV Foundation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "precomp.hpp"
#include "caffe/layer_loaders.hpp"
#include "layers/blank_layer.hpp"
#include "layers/elementwise_layers.hpp"
#include "layers/fully_connected_layer.hpp"
#include "layers/lrn_layer.hpp"
#include "layers/mvn_layer.hpp"
#include "layers/pooling_layer.hpp"
#include "layers/reshape_layer.hpp"
#include "layers/slice_layer.hpp"
#include "layers/softmax_layer.hpp"
#include "layers/split_layer.hpp"
#include "layers/crop_layer.hpp"
#include "layers/eltwise_layer.hpp"
#include "layers/flatten_layer.hpp"
#include "layers/permute_layer.hpp"
#include "layers/prior_box_layer.hpp"
#include "layers/detection_output_layer.hpp"
#include "layers/normalize_bbox_layer.hpp"

namespace cv
{
namespace dnn
{

struct AutoInitializer
{
    bool status;

    AutoInitializer() : status(false)
    {
        cv::dnn::initModule();
    }
};

static AutoInitializer init;

void initModule()
{
    if (init.status)
        return;

    REG_RUNTIME_LAYER_FUNC(Slice,           createLayerFromCaffe<SliceLayer>);
    REG_RUNTIME_LAYER_FUNC(Split,           createLayerFromCaffe<SplitLayer>);
    REG_RUNTIME_LAYER_FUNC(Concat,          createLayerFromCaffe<ConcatLayer>);
    REG_RUNTIME_LAYER_FUNC(Reshape,         createLayerFromCaffe<ReshapeLayer>);

    REG_RUNTIME_LAYER_FUNC(Convolution,     createLayerFromCaffe<ConvolutionLayer>);
    REG_RUNTIME_LAYER_FUNC(Deconvolution,   createLayerFromCaffe<DeconvolutionLayer>);
    REG_RUNTIME_LAYER_FUNC(Pooling,         createLayerFromCaffe<PoolingLayer>);
    REG_RUNTIME_LAYER_FUNC(LRN,             createLayerFromCaffe<LRNLayer>);
    REG_RUNTIME_LAYER_FUNC(InnerProduct,    createLayerFromCaffe<InnerProductLayer>);
    REG_RUNTIME_LAYER_FUNC(Softmax,         createLayerFromCaffe<SoftmaxLayer>);
    REG_RUNTIME_LAYER_FUNC(MVN,             createLayerFromCaffe<MVNLayer>);

    REG_RUNTIME_LAYER_FUNC(ReLU,            createLayerFromCaffe<ReLULayer>);
    REG_RUNTIME_LAYER_FUNC(Sigmoid,         createLayerFromCaffe<SigmoidLayer>);
    REG_RUNTIME_LAYER_FUNC(TanH,            createLayerFromCaffe<TanHLayer>);
    REG_RUNTIME_LAYER_FUNC(BNLL,            createLayerFromCaffe<BNLLLayer>);
    REG_RUNTIME_LAYER_FUNC(AbsVal,          createLayerFromCaffe<AbsLayer>);
    REG_RUNTIME_LAYER_FUNC(Power,           createLayerFromCaffe<PowerLayer>);
    REG_RUNTIME_LAYER_CLASS(Dropout,        BlankLayer);

    REG_RUNTIME_LAYER_CLASS(Crop,           CropLayer);

    REG_RUNTIME_LAYER_CLASS(Permute,        createLayerFromCaffe<PermuteLayer>);
    REG_RUNTIME_LAYER_CLASS(Flatten,        createLayerFromCaffe<FlattenLayer>);
    REG_RUNTIME_LAYER_CLASS(PriorBox,       createLayerFromCaffe<PriorBoxLayer>);
    REG_RUNTIME_LAYER_CLASS(DetectionOutput, createLayerFromCaffe<DetectionOutputLayer>);
    REG_RUNTIME_LAYER_CLASS(NormalizeBBox,   createLayerFromCaffe<NormalizeBBoxLayer>);

    init.status = true;
}

}
}
