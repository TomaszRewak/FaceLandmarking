#pragma once

#include "image-feature-extractor.hpp"
#include "mask-feature-extractor.hpp"

namespace FaceLandmarking::FeatureExtraction
{
	template<size_t N>
	class FeatureExtractor
	{
	private:
		ImageFeatureExtractor imageFeatrues;
		MaskFeatureExtractor<N> maskFeatures;

	public:
		void setImage(const HsvImage& image)
		{
			imageFeatrues.setImage(image);
		}

		void selectFeatures(const FaceMask<N>& mask, int maskPoint, std::vector<float>& features)
		{
			auto[x, y] = mask[maskPoint];

			imageFeatrues.selectFeatures(x, y, features);
			//maskFeatures.selectFeatures(mask, maskPoint, features);
		}
	};
}