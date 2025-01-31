// Distributed under the MIT License.
// See LICENSE.txt for details.

#include "PointwiseFunctions/GeneralRelativity/ProjectionOperators.hpp"

#include "DataStructures/Tensor/Tensor.hpp"
#include "Utilities/ContainerHelpers.hpp"
#include "Utilities/GenerateInstantiations.hpp"
#include "Utilities/Gsl.hpp"

/// \cond
namespace gr {
template <size_t VolumeDim, typename Frame, typename DataType>
tnsr::II<DataType, VolumeDim, Frame> transverse_projection_operator(
    const tnsr::II<DataType, VolumeDim, Frame>& inverse_spatial_metric,
    const tnsr::I<DataType, VolumeDim, Frame>& normal_vector) noexcept {
  tnsr::II<DataType, VolumeDim, Frame> projection_tensor(
      get_size(get<0>(normal_vector)));
  transverse_projection_operator(make_not_null(&projection_tensor),
                                 inverse_spatial_metric, normal_vector);
  return projection_tensor;
}

template <size_t VolumeDim, typename Frame, typename DataType>
void transverse_projection_operator(
    const gsl::not_null<tnsr::II<DataType, VolumeDim, Frame>*>
        projection_tensor,
    const tnsr::II<DataType, VolumeDim, Frame>& inverse_spatial_metric,
    const tnsr::I<DataType, VolumeDim, Frame>& normal_vector) noexcept {
  destructive_resize_components(projection_tensor,
                                get_size(get<0>(normal_vector)));

  for (size_t i = 0; i < VolumeDim; ++i) {
    for (size_t j = i; j < VolumeDim; ++j) {
      projection_tensor->get(i, j) =
          inverse_spatial_metric.get(i, j) -
          normal_vector.get(i) * normal_vector.get(j);
    }
  }
}

template <size_t VolumeDim, typename Frame, typename DataType>
tnsr::ii<DataType, VolumeDim, Frame> transverse_projection_operator(
    const tnsr::ii<DataType, VolumeDim, Frame>& spatial_metric,
    const tnsr::i<DataType, VolumeDim, Frame>& normal_one_form) noexcept {
  tnsr::ii<DataType, VolumeDim, Frame> projection_tensor(
      get_size(get<0>(normal_one_form)));
  transverse_projection_operator(make_not_null(&projection_tensor),
                                 spatial_metric, normal_one_form);
  return projection_tensor;
}

template <size_t VolumeDim, typename Frame, typename DataType>
void transverse_projection_operator(
    const gsl::not_null<tnsr::ii<DataType, VolumeDim, Frame>*>
        projection_tensor,
    const tnsr::ii<DataType, VolumeDim, Frame>& spatial_metric,
    const tnsr::i<DataType, VolumeDim, Frame>& normal_one_form) noexcept {
  destructive_resize_components(projection_tensor,
                                get_size(get<0>(normal_one_form)));

  for (size_t i = 0; i < VolumeDim; ++i) {
    for (size_t j = i; j < VolumeDim; ++j) {
      projection_tensor->get(i, j) =
          spatial_metric.get(i, j) -
          normal_one_form.get(i) * normal_one_form.get(j);
    }
  }
}

template <size_t VolumeDim, typename Frame, typename DataType>
tnsr::Ij<DataType, VolumeDim, Frame> transverse_projection_operator(
    const tnsr::I<DataType, VolumeDim, Frame>& normal_vector,
    const tnsr::i<DataType, VolumeDim, Frame>& normal_one_form) noexcept {
  tnsr::Ij<DataType, VolumeDim, Frame> projection_tensor(
      get_size(get<0>(normal_vector)));
  transverse_projection_operator(make_not_null(&projection_tensor),
                                 normal_vector, normal_one_form);
  return projection_tensor;
}

template <size_t VolumeDim, typename Frame, typename DataType>
void transverse_projection_operator(
    const gsl::not_null<tnsr::Ij<DataType, VolumeDim, Frame>*>
        projection_tensor,
    const tnsr::I<DataType, VolumeDim, Frame>& normal_vector,
    const tnsr::i<DataType, VolumeDim, Frame>& normal_one_form) noexcept {
  destructive_resize_components(projection_tensor,
                                get_size(get<0>(normal_vector)));

  for (size_t i = 0; i < VolumeDim; ++i) {
    for (size_t j = 0; j < VolumeDim; ++j) {
      projection_tensor->get(i, j) =
          -normal_vector.get(i) * normal_one_form.get(j);
    }
    projection_tensor->get(i, i) += 1.;
  }
}
// @}
}  // namespace gr

#define DIM(data) BOOST_PP_TUPLE_ELEM(0, data)
#define DTYPE(data) BOOST_PP_TUPLE_ELEM(1, data)
#define FRAME(data) BOOST_PP_TUPLE_ELEM(2, data)

#define INSTANTIATE(_, data)                                               \
  template tnsr::II<DTYPE(data), DIM(data), FRAME(data)>                   \
  gr::transverse_projection_operator(                                      \
      const tnsr::II<DTYPE(data), DIM(data), FRAME(data)>&                 \
          inverse_spatial_metric,                                          \
      const tnsr::I<DTYPE(data), DIM(data), FRAME(data)>&                  \
          normal_vector) noexcept;                                         \
  template tnsr::ii<DTYPE(data), DIM(data), FRAME(data)>                   \
  gr::transverse_projection_operator(                                      \
      const tnsr::ii<DTYPE(data), DIM(data), FRAME(data)>& spatial_metric, \
      const tnsr::i<DTYPE(data), DIM(data), FRAME(data)>&                  \
          normal_one_form) noexcept;                                       \
  template tnsr::Ij<DTYPE(data), DIM(data), FRAME(data)>                   \
  gr::transverse_projection_operator(                                      \
      const tnsr::I<DTYPE(data), DIM(data), FRAME(data)>& normal_vector,   \
      const tnsr::i<DTYPE(data), DIM(data), FRAME(data)>&                  \
          normal_one_form) noexcept;                                       \
  template void gr::transverse_projection_operator(                        \
      const gsl::not_null<tnsr::II<DTYPE(data), DIM(data), FRAME(data)>*>  \
          projection_tensor,                                               \
      const tnsr::II<DTYPE(data), DIM(data), FRAME(data)>&                 \
          inverse_spatial_metric,                                          \
      const tnsr::I<DTYPE(data), DIM(data), FRAME(data)>&                  \
          normal_vector) noexcept;                                         \
  template void gr::transverse_projection_operator(                        \
      const gsl::not_null<tnsr::ii<DTYPE(data), DIM(data), FRAME(data)>*>  \
          projection_tensor,                                               \
      const tnsr::ii<DTYPE(data), DIM(data), FRAME(data)>& spatial_metric, \
      const tnsr::i<DTYPE(data), DIM(data), FRAME(data)>&                  \
          normal_one_form) noexcept;                                       \
  template void gr::transverse_projection_operator(                        \
      const gsl::not_null<tnsr::Ij<DTYPE(data), DIM(data), FRAME(data)>*>  \
          projection_tensor,                                               \
      const tnsr::I<DTYPE(data), DIM(data), FRAME(data)>& normal_vector,   \
      const tnsr::i<DTYPE(data), DIM(data), FRAME(data)>&                  \
          normal_one_form) noexcept;

GENERATE_INSTANTIATIONS(INSTANTIATE, (1, 2, 3), (double, DataVector),
                        (Frame::Grid, Frame::Inertial))

#undef DIM
#undef DTYPE
#undef FRAME
#undef INSTANTIATE
/// \endcond
