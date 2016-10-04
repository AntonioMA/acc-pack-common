//
//  OTOneToOneCommunicator.h
//
//  Copyright © 2016 Tokbox, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

typedef NS_ENUM(NSUInteger, OTOneToOneCommunicationSignal) {
    OTSessionDidConnect = 0,
    OTSessionDidDisconnect,
    OTSessionDidFail,
    OTSessionStreamCreated,
    OTSessionStreamDestroyed,
    OTSessionConnectionCreated,
    OTSessionConnectionDestroyed,
    OTSessionConnectionDidBeginReconnecting,
    OTSessionConnectionDidReconnect,
    OTPublisherDidFail,
    OTPublisherStreamCreated,
    OTPublisherStreamDestroyed,
    OTSubscriberDidConnect,
    OTSubscriberDidFail,
    OTSubscriberVideoDisabledByPublisher,
    OTSubscriberVideoDisabledBySubscriber,
    OTSubscriberVideoDisabledByBadQuality,
    OTSubscriberVideoEnabledByPublisher,
    OTSubscriberVideoEnabledBySubscriber,
    OTSubscriberVideoEnabledByGoodQuality,
    OTSubscriberVideoDisableWarning,
    OTSubscriberVideoDisableWarningLifted,
};

typedef void (^OTOneToOneCommunicatorBlock)(OTOneToOneCommunicationSignal signal, NSError *error);

@protocol OTOneToOneCommunicatorDelegate <NSObject>
- (void)oneToOneCommunicationWithSignal:(OTOneToOneCommunicationSignal)signal
                                  error:(NSError *)error;
@end

@interface OTOneToOneCommunicator: NSObject

/**
 *  @return Returns the shared OTOneToOneCommunicator object.
 */
+ (instancetype)sharedInstance;

/**
 *  Registers to the shared session: [OTAcceleratorSession] and perform publishing/subscribing automatically.
 *
 *  @return An error to indicate whether it connects successfully, non-nil if it fails.
 */
- (NSError *)connect;

/**
 *  An alternative connect method with a completion block handler.
 *
 *  @param handler The completion handler to call with the change.
 */
- (void)connectWithHandler:(OTOneToOneCommunicatorBlock)handler;

/**
 *  De-registers to the shared session: [OTAcceleratorSession] and stops publishing/subscriber.
 *
 *  @return An error to indicate whether it disconnects successfully, non-nil if it fails.
 */
- (NSError *)disconnect;

@property (weak, nonatomic) id<OTOneToOneCommunicatorDelegate> delegate;

/**
 *  A boolean value to indicate whether the call is enabled. `YES` once the publisher connects or after OTSessionDidConnect being signaled.
 */
@property (readonly, nonatomic) BOOL isCallEnabled;

#pragma mark - subscriber
/**
 *  The view containing a playback buffer for associated video data. Add this view to your view heirarchy to display a video stream.
 *
 *  The subscriber view is available after OTSubscriberDidConnect being signaled.
 */
@property (readonly, nonatomic) UIView *subscriberView;

/**
 *  A boolean value to indicate whether the subscriber subscribes to the stream's audio.
 */
@property (nonatomic, getter=isSubscribeToAudio) BOOL subscribeToAudio;

/**
 *  A boolean value to indicate whether the subscriber subscribes to the stream's video.
 */
@property (nonatomic, getter=isSubscribeToVideo) BOOL subscribeToVideo;

#pragma mark - publisher
/**
 *  A string that will be associated with this publisher's stream.
 */
@property (nonatomic) NSString *publisherName;

/**
 *  The view for this publisher. If this view becomes visible, it will display a preview of the active camera feed.
 * 
 *  The publisher view is available after OTSessionDidConnect being signaled.
 */
@property (readonly, nonatomic) UIView *publisherView;

/**
 *  A boolean value to indicate whether to publish audio.
 */
@property (nonatomic, getter=isPublishAudio) BOOL publishAudio;

/**
 *  A boolean value to indicate whether to publish video.
 */
@property (nonatomic, getter=isPublishVideo) BOOL publishVideo;

/**
 *  The preferred camera position. When setting this property, if the change is possible, the publisher will use the camera with the specified position. 
 *  If the publisher has begun publishing, getting this property returns the current camera position; 
 *  if the publisher has not yet begun publishing, getting this property returns the preferred camera position.
 */
@property (nonatomic) AVCaptureDevicePosition cameraPosition;

@end
