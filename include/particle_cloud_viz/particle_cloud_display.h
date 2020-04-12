/*
 * Copyright (c) 2012, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RVIZ_PARTICLE_CLOUD_DISPLAY_H_
#define RVIZ_PARTICLE_CLOUD_DISPLAY_H_

#include <particle_filter_msgs/ParticleCloud.h>

#include "rviz/message_filter_display.h"

namespace Ogre
{
class ManualObject;
}

namespace rviz
{

class EnumProperty;
class ColorProperty;
class FloatProperty;
class Arrow;
class Axes;

/** @brief Displays a particle_filter_msgs/ParticleCloud message as a bunch of
 * 				 weighted line-drawn arrows. */
class ParticleCloudDisplay: public MessageFilterDisplay<particle_filter_msgs::ParticleCloud>
{
Q_OBJECT
public:
  ParticleCloudDisplay();
  virtual ~ParticleCloudDisplay();

protected:
  virtual void onInitialize();
  virtual void reset();
  virtual void processMessage( const particle_filter_msgs::ParticleCloudConstPtr& msg );

private:
  bool setTransform(std_msgs::Header const & header);
  void updateArrows2d();
  void updateArrows3d();
  void updateAxes();
  void updateDisplay();
	std::unique_ptr<Axes> makeAxes();
	std::unique_ptr<Arrow> makeArrow3d();

  struct OgrePose {
    Ogre::Vector3 position;
    Ogre::Quaternion orientation;
  };

  std::vector<OgrePose> poses_;
	std::vector<float> weights_;
	std::vector<std::unique_ptr<Arrow>> arrows3d_;
	std::vector<std::unique_ptr<Axes>> axes_;

  Ogre::SceneNode * arrow_node_;
  Ogre::SceneNode * axes_node_;
  Ogre::ManualObject* manual_object_;

  EnumProperty* shape_property_;
  ColorProperty* arrow_color_property_;
  FloatProperty* arrow_alpha_property_;

  FloatProperty* arrow2d_length_property_;

  FloatProperty* arrow3d_head_radius_property_;
  FloatProperty* arrow3d_head_length_property_;
  FloatProperty* arrow3d_shaft_radius_property_;
  FloatProperty* arrow3d_shaft_length_property_;

  FloatProperty* axes_length_property_;
  FloatProperty* axes_radius_property_;

private Q_SLOTS:
  /// Update the interface and visible shapes based on the selected shape type.
  void updateShapeChoice();

  /// Update the arrow color.
  void updateArrowColor();

  /// Update the flat arrow geometry.
  void updateArrow2dGeometry();

  /// Update the 3D arrow geometry.
  void updateArrow3dGeometry();

  /// Update the axes geometry.
  void updateAxesGeometry();
};

} // namespace rviz

#endif /* RVIZ_PARTICLE_CLOUD_DISPLAY_H_ */
