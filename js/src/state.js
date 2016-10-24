// Map publisher ids to publisher objects
const publishers = {
  camera: {},
  screen: {},
};

// Map subscriber id to subscriber objects
const subscribers = {
  camera: {},
  screen: {},
};

// Map stream ids to stream objects
const streams = {};

// Map stream ids to subscriber/publisher ids
const streamMap = {};



/**
 * Returns the count of current publishers and subscribers by type
 * @retuns {Object}
 *    {
 *      publishers: {
 *        camera: 1,
 *        screen: 1,
 *        total: 2
 *      },
 *      subscribers: {
 *        camera: 3,
 *        screen: 1,
 *        total: 4
 *      }
 *   }
 */
const pubSubCount = () => {
  const pubs = Object.keys(publishers).reduce((acc, source) => {
    acc[source] = Object.keys(publishers[source]).length;
    acc.total += acc[source];
    return acc;
  }, { camera: 0, screen: 0, total: 0 });

  const subs = Object.keys(subscribers).reduce((acc, source) => {
    acc[source] = Object.keys(subscribers[source]).length;
    acc.total += acc[source];
    return acc;
  }, { camera: 0, screen: 0, total: 0 });

  return { publisher: pubs, subscriber: subs };
};

/**
 * Returns the current publishers and subscribers, along with a count of each
 */
const currentPubSub = () => ({ publishers, subscribers, meta: pubSubCount() });

const addPublisher = (type, publisher) => {
  streamMap[publisher.streamId] = publisher.id;
  publishers[type][publisher.id] = publisher;
};

const removePublisher = (type, publisher) => {
  const id = publisher.id || streamMap[publisher.streamId];
  delete publishers[type][id];
};

const removeAllPublishers = () => {
  publishers.camera = {};
  publishers.screen = {};
};

const addSubscriber = (subscriber) => {
  const type = subscriber.stream.videoType;
  const streamId = subscriber.stream.id;
  subscribers[type][subscriber.id] = subscriber;
  streamMap[streamId] = subscriber.id;
};

const removeSubscriber = (subscriber = {}) => {
  const { stream } = subscriber;
  const type = stream && stream.videoType;
  delete subscribers[type][subscriber.id];
};

const addStream = (stream) => {
  streams[stream.id] = stream;
};

const removeStream = (stream) => {
  const type = stream.videoType;
  const subscriberId = streamMap[stream.id];
  delete streamMap[stream.id];
  delete streams[stream.id];
  removeSubscriber(subscribers[type][subscriberId]);
};

const getStreams = () => streams;

const all = () => Object.assign({}, currentPubSub(), { streams, streamMap });

module.exports = {
  addStream,
  removeStream,
  getStreams,
  addPublisher,
  removePublisher,
  removeAllPublishers,
  addSubscriber,
  currentPubSub,
  all,
};
