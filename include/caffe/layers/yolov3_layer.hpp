#ifndef CAFFE_YOLOV3_LAYER_HPP_
#define CAFFE_YOLOV3_LAYER_HPP_

#include <vector>
#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"
#include <string>
#include "caffe/layers/loss_layer.hpp"
#include <map>

namespace caffe {


template <typename Dtype>
class Yolov3Layer : public LossLayer<Dtype> {
public:
	explicit Yolov3Layer(const LayerParameter& param)
		: LossLayer<Dtype>(param), diff_() {}
	virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
		const vector<Blob<Dtype>*>& top);
	virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
		const vector<Blob<Dtype>*>& top);

	virtual inline const char* type() const { return "Yolov3"; }
	
	template <typename Dtype>
	class PredictionResult {
	public:
		Dtype x;
		Dtype y;
		Dtype w;
		Dtype h;
		Dtype objScore;
		Dtype classScore;
		Dtype confidence;
		int classType;
	};

	protected:
	virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
		const vector<Blob<Dtype>*>& top);
	// virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
	//     const vector<Blob<Dtype>*>& top);

	virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
		const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
	// virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
	//     const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
	int iter_;
	int side_;
	int num_class_;
	int num_;
	int anchors_scale_;
	float object_scale_;
	float class_scale_;
	float noobject_scale_;
	float coord_scale_;
	float thresh_;
	vector<Dtype> biases_;
	vector<Dtype> mask_;
	Blob<Dtype> diff_;
	Blob<Dtype> real_diff_;
	Blob<Dtype> swap_;
	AvgRegionScore score_;
};

}  // namespace caffe

#endif  // CAFFE_REGION_LOSS_LAYER_HPP_
