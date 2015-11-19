/*
 * Copyright (C) 2015 Fondazione Istituto Italiano di Tecnologia
 * Authors: Silvio Traversaro
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef IDYNTREE_MODEL_H
#define IDYNTREE_MODEL_H

#include <iDynTree/Model/IJoint.h>
#include <iDynTree/Model/Link.h>
#include <iDynTree/Core/Transform.h>

#include <iDynTree/Model/Indeces.h>

#include <cstdlib>
#include <vector>

namespace iDynTree
{
    class Traversal;

    struct Neighbor
    {
        LinkIndex neighborLink;
        JointIndex neighborJoint;
    };

    /**
     * Class that represents a generic multibody model.
     *
     * A model is composed by rigid bodies (i.e. links) connected
     * by joints. Each joint can have from 0 to 6 degrees of freedom.
     *
     * Each link has a "link frame" rigidly attached to it.
     * For each link additional rigidly attached frames can be defined,
     * in addition to "link frame".
     *
     * The model contains also a serialization for the different elements
     *  in a model, i.e. a function between:
     *  * joint names and the integers 0..getNrOfJoints()-1
     *  * dof   names and the integers 0..getNrOfDOFs()-1
     *  * link  names and the integers 0..getNrOfLinks()-1
     *  * frame names and the integers 0..getNrOfFrames()-1
     *
     * For simplicity, this mappings are build when building the model.
     *
     * In particular the joint and link indices are assigned when the links
     * and joint are added to the model using the `addLink` and `addJoint`
     * methods.
     *
     * The DOF indeces are also assigned when the joint is added to the model
     * with the addJoint method. For example if a model is composed only of
     * 0 or 1 DOF joints and the 1 DOFs joints are added before the 0 DOFs then
     * the joint index and dof index for 1 DOF joints will be coincident (this is
     * how the URDF parser is actually implemented). For this reason as the moment
     * there is no concept of DOF explicit identifier, i.e. no getDOFName(DOFIndex dofIndex)
     * method.
     *
     * The frame indices between 0 and getNrOfFrames()-1 are always assigned to the
     * "main" link frame of the link with the same index.
     *
     *
     * \ingroup iDynTreeModel
     */
    class Model
    {
    private:
        /** Vector of links. For each link its index indicates its location in this vector */
        std::vector<Link> links;

        /** Vector of joints. For each joint its index indicates its location in this vector */
        std::vector<IJointPtr> joints;

        /** Vector of additional frames.
         *  The element additionalFrames[frameOffset] will be the link_H_frame transform  of the frame with
         *  FrameIndex getNrOfLinks() + frameOffset .
         */
        std::vector<Transform> additionalFrames;

        /** Vector of link indeces corresponding to an additional frame.
         *  The element additionalFrameNames[frameOffset] will be the link_H_frame transform  of the frame with
         *  FrameIndex getNrOfLinks() + frameOffset .
         */
        std::vector<LinkIndex> additionalFramesLinks;

        /** Vector of link names, matches the index of each link to its name. */
        std::vector<std::string> linkNames;

        /** Vector of joint names, matches the index of each joint to its name. */
        std::vector<std::string> jointNames;

        /** Vector of additional frame names.
         *  The element frameNames[frameOffset] will be the name of the frame with
         *  FrameIndex getNrOfLinks() + frameOffset .
         */
        std::vector<std::string> frameNames;

        /** Adjacency lists: match each link index to a list of its neighbors,
            and the joint connecting to them. */
        std::vector< std::vector<Neighbor> > neighbors;

        /**
         * Most data structures are not undirected, so we store the original
         * root of the tree, to provide a default root for Traversal generation.
         */
        LinkIndex defaultBaseLink;

        /**
         * Cache number of position coordinaties of the model.
         * If all joints are 0 or 1 dofs, this is equal to nrOfDOFs.
         */
        unsigned int nrOfPosCoords;

        /**
         * Cached number of (internal) DOFs of the model.
         *  This is just the sum of all the getNrOfDOFs of the joint in the model.
         */
        unsigned int nrOfDOFs;

        /**
         * Check if a name is already used for a link in the model.
         *
         * @return true if a name is used by a link in a model, false otherwise.
         */
        bool isLinkNameUsed(const std::string linkName);

        /**
         * Check if a name is already used for a joint in the model.
         *
         * @return true if a name is used by a joint in a model, false otherwise.
         */
        bool isJointNameUsed(const std::string jointName);

        /**
         * Check if a name is already used for a frame in the model.
         *
         * \note this function will check the name of the links and the names of the additional frames.
         * @return true if a name is used by a frame in a model, false otherwise.
         */
        bool isFrameNameUsed(const std::string frameName);

        /**
         * Copy the structure of the model from another instance of a model.
         */
        void copy(const Model & model);

        /**
         * Destroy the object, properly deallocating memory.
         */
        void destroy();

    public:

        /**
         * Costructor
         */
        Model();

        /**
         * Copy costructor
         */
        Model(const Model & other);

        /**
         * Copy operator
         */
        Model& operator=(const Model &other);

        /**
         * Destructor
         *
         */
        virtual ~Model();

        /**
         * Get the number of links in the model.
         */
        size_t getNrOfLinks() const;

        /**
         * Get the name of a link given its index, or
         * an LINK_INVALID_NAME string if linkIndex < 0 or >= getNrOfLinks()
         */
        std::string  getLinkName(const LinkIndex linkIndex) const;

        LinkIndex getLinkIndex(const std::string & linkName) const;

        LinkPtr getLink(const LinkIndex linkIndex);
        LinkConstPtr getLink(const LinkIndex linkIndex) const;

        LinkIndex addLink(const std::string & name, const Link & link);

        /**
         * Get number of joints in the model.
         */
        size_t getNrOfJoints() const;

        /**
         * Get the name of a link given its index, or
         * an JOINT_INVALID_NAME if linkIndex < 0 or >= getNrOfLinks()
         */
        std::string getJointName(const JointIndex index) const;

        /**
         * Get the index of a joint, given a jointName.
         * If the jointName is not found in the model,
         * return JOINT_INVALID_INDEX .
         *
         */
        JointIndex getJointIndex(const std::string & jointName) const;

        IJointPtr getJoint(const JointIndex index);

        IJointConstPtr getJoint(const JointIndex index) const;

        /**
         *
         * @return the JointIndex of the added joint, or JOINT_INVALID_INDEX if
         *         there was an error in adding the joint.
         */
        JointIndex addJoint(const std::string & jointName, IJointConstPtr joint);

        /**
         * Get the dimension of the vector used to parametrize the positions of the joints of the robot.
         * This number can be obtained by summing the getNrOfPosCoords of all the joints of the model.
         *
         * \warning This is *not* including the 6 degrees of freedom of the base.
         */
        size_t getNrOfPosCoords() const;

        /**
         * Get the number of degrees of freedom of the joint of the robot.
         * This number can be obtained by summing the getNrOfDOFs of all the joints of the model.
         *
         * \warning This is *not* including the 6 degrees of freedom of the base.
         */
        size_t getNrOfDOFs() const;

        /**
         * Get the number of frames in the model.
         *
         * \note this will return the sum of the number of link
         *       (as each link has an attached frame) and the total number
         *       of additional frames.
         *
         * @return the number of frames in the model.
         */
        size_t getNrOfFrames() const;

        /**
         * Add an additional frame to a link.
         *
         * \note This function has signature different from
         *       addJoint/addLink because the FrameIndex of the
         *       additional frame are invalidated at each call to
         *       the addLink. So we don't return the FrameIndex in this
         *       function, as the model construction should be completed
         *       before that FrameIndex are stored.
         *
         * @param[in] linkName the link to which attach the additional frame.
         * @param[in] frameName the name of the frame added to the model.
         * @param[in] link_H_frame the pose of added frame with respect to the link main frame,
         *                         expressed with a transform with:
         *                              refFrame: the main link frame
         *                              frame: the added frame
         * @return true if all went well, false if an error occured.
         *
         */
        bool addAdditionalFrameToLink(const std::string & linkName,
                                      const std::string & frameName,
                                      iDynTree::Transform link_H_frame);

        /**
         * Get the name of a frame given its index.
         *
         * @param[in] frameIndex the index of the frame whose name is requested.
         * @return the name of a frame given its index, or
         *         a FRAME_INVALID_NAME string if frameIndex < 0 or >= getNrOfFrames()
         */
        std::string  getFrameName(const FrameIndex frameIndex) const;

        /**
         * Get the index of a frame given its name.
         *
         * @param[in] frameName the name of the frame for which the index is requested.
         * @return    the index of the frame, of FRAME_INVALID_INDEX if frameName is not
         *            not a frame name.
         */
        FrameIndex getFrameIndex(const std::string & frameName) const;

        /**
         * Get the tranform of the frame with respect to the main
         * frame of the link, returned as link_H_frame tranform
         * with refFrame : the link main frame and frame : the
         *  frame with index frameIndex .
         *
         * @param[in] frameIndex the index of the frame for which
         * @return the link_H_frame transform, or an identity tranform
         *         if frameIndex < 0 or frameIndex >= getNrOfFrames .
         */
        Transform getFrameTransform(const FrameIndex frameIndex) const;

        /**
         * Get the link at which the frame with index frameIndex
         * is attached.
         *
         */
        LinkIndex getFrameLink(const FrameIndex frameIndex) const;

        /**
         * Get the nr of neighbors of a given link.
         */
        unsigned int getNrOfNeighbors(const LinkIndex link) const;

        /**
         * Get the neighbor of a link. neighborIndex should be
         * >= 0 and <= getNrOfNeighbors(link)
         */
        Neighbor getNeighbor(const LinkIndex link, unsigned int neighborIndex) const;

        /**
         * Set the default base link, used for generation of the default traversal.
         */
        bool setDefaultBaseLink(const LinkIndex linkIndex);

        /**
         * Get the default base link, used for generation of the default traversal.
         */
        LinkIndex getDefaultBaseLink() const;

        /**
         * Compute a Traversal of all the links in the Model, doing a Depth First Search starting
         * at the default base.
         *
         * \warning The traversal computed with this function contains pointers to the joints
         *          and links present in this model. Whener this pointer are invalidated,
         *          for example because a link or a joint is added or the model is copied,
         *          the traversal need to be recomputed.
         *
         * \warning this function works only on Models without cycles.
         */
        bool computeFullTreeTraversal(Traversal & traversal) const;

       /**
         * Compute a Traversal of all the links in the Model, doing a Depth First Search starting
         * at the given traversalBase.
         *
         * \warning The traversal computed with this function contains pointers to the joints
         *          and links present in this model. Whener this pointer are invalidated,
         *          for example because a link or a joint is added or the model is copied,
         *          the traversal need to be recomputed.
         *
         * \warning this function works only on Models without cycles.
         */
        bool computeFullTreeTraversal(Traversal & traversal, const LinkIndex traversalBase) const;

    };


}

#endif /* IDYNTREE_LINK_H */