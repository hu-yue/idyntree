classdef FreeFloatingGeneralizedTorques < SwigRef
  methods
    function this = swig_this(self)
      this = iDynTreeMEX(3, self);
    end
    function self = FreeFloatingGeneralizedTorques(varargin)
      if nargin==1 && strcmp(class(varargin{1}),'SwigRef')
        if ~isnull(varargin{1})
          self.swigPtr = varargin{1}.swigPtr;
        end
      else
        tmp = iDynTreeMEX(1193, varargin{:});
        self.swigPtr = tmp.swigPtr;
        tmp.swigPtr = [];
      end
    end
    function varargout = resize(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1194, self, varargin{:});
    end
    function varargout = baseWrench(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1195, self, varargin{:});
    end
    function varargout = jointTorques(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1196, self, varargin{:});
    end
    function varargout = getNrOfDOFs(self,varargin)
      [varargout{1:nargout}] = iDynTreeMEX(1197, self, varargin{:});
    end
    function delete(self)
      if self.swigPtr
        iDynTreeMEX(1198, self);
        self.swigPtr=[];
      end
    end
  end
  methods(Static)
  end
end
