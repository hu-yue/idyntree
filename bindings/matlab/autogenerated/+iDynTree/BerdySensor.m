classdef BerdySensor < SwigRef
  methods
    function this = swig_this(self)
      this = iDynTreeMEX(3, self);
    end
    function varargout = type(self, varargin)
      narginchk(1, 2)
      if nargin==1
        nargoutchk(0, 1)
        varargout{1} = iDynTreeMEX(1489, self);
      else
        nargoutchk(0, 0)
        iDynTreeMEX(1490, self, varargin{1});
      end
    end
    function varargout = id(self, varargin)
      narginchk(1, 2)
      if nargin==1
        nargoutchk(0, 1)
        varargout{1} = iDynTreeMEX(1491, self);
      else
        nargoutchk(0, 0)
        iDynTreeMEX(1492, self, varargin{1});
      end
    end
    function varargout = range(self, varargin)
      narginchk(1, 2)
      if nargin==1
        nargoutchk(0, 1)
        varargout{1} = iDynTreeMEX(1493, self);
      else
        nargoutchk(0, 0)
        iDynTreeMEX(1494, self, varargin{1});
      end
    end
    function varargout = eq(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1495, self, varargin{:});
    end
    function varargout = lt(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1496, self, varargin{:});
    end
    function self = BerdySensor(varargin)
      if nargin==1 && strcmp(class(varargin{1}),'SwigRef')
        if ~isnull(varargin{1})
          self.swigPtr = varargin{1}.swigPtr;
        end
      else
        tmp = iDynTreeMEX(1497, varargin{:});
        self.swigPtr = tmp.swigPtr;
        tmp.swigPtr = [];
      end
    end
    function delete(self)
      if self.swigPtr
        iDynTreeMEX(1498, self);
        self.swigPtr=[];
      end
    end
  end
  methods(Static)
  end
end
